import network
import json
import os
import ntptime
import machine
from time import ticks_ms, localtime, sleep_ms
from esp32 import RMT
from time import sleep
from machine import SPI, SoftSPI, Timer, Pin
from time import sleep_ms

# Timezone settings
CONFIG_TIMEZONE = 2
CONFIG_DAYLIGHT_SAVING_ENABLED = True
CONFIG_NTP_SYNC_INTERVAL_HOURS = 24

# General animation settings
CONFIG_CPU_FREQUENCY = 80000000
CONFIG_RMT_DIVISOR = 255
CONFIG_REFRESH_RATE = 100

# Night time dimming configuration
CONFIG_DIMMING_ENABLED = True
CONFIG_DIMMING_BRIGHTNESS = 0.4
CONFIG_DIMMING_START = 15
CONFIG_DIMMING_END = 6
CONFIG_DIMMING_GAMMA = 2.2

# Daytime frame blending configuration
CONFIG_BLENDING_ENABLED = True
CONFIG_BLENDING_DURATION = 150

# Wireless networks
CONFIG_NETWORKS = {
    "k-space.ee legacy": "",
}

try:
    from config import *
except ImportError:
    print("Upload config.py to override configuration")
except:
    print("Failed to load config.py")

assert CONFIG_TIMEZONE >= -12
assert CONFIG_TIMEZONE < 14
assert CONFIG_DAYLIGHT_SAVING_ENABLED in (True, False)
assert CONFIG_CPU_FREQUENCY in (80000000, 160000000, 240000000)
assert CONFIG_DIMMING_BRIGHTNESS >= 0
assert CONFIG_DIMMING_BRIGHTNESS <= 1
assert CONFIG_DIMMING_START >= 12
assert CONFIG_DIMMING_START <= 23
assert CONFIG_DIMMING_END >= 1
assert CONFIG_DIMMING_END < 12
assert CONFIG_DIMMING_GAMMA >= 1
assert CONFIG_BLENDING_DURATION < 500
assert CONFIG_BLENDING_DURATION >= 0
assert CONFIG_RMT_DIVISOR >= 1
assert CONFIG_RMT_DIVISOR <= 255

print("Setting CPU frequency to", CONFIG_CPU_FREQUENCY // 1000000, "MHz")
machine.freq(CONFIG_CPU_FREQUENCY)

sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)
for jssid, _, _, _, _, _ in sta_if.scan():
    ssid = jssid.decode("utf-8")
    if ssid in CONFIG_NETWORKS:
        sta_if.connect(ssid, CONFIG_NETWORKS[ssid])
        print("Connecting to", ssid, "...")
        while not sta_if.isconnected():
            pass
        print("Obtained DHCP lease for", sta_if.ifconfig()[0])
        ntptime.settime()
        sta_if.active(False)
        break
else:
    print("No configured wireless network found")

print("Press Ctrl-C now to abort main.py execution and retain keyboard input")
sleep_ms(2000)

clock = Pin(20, mode=Pin.OUT)
latch = Pin(9, mode=Pin.OUT)
data = Pin(2, mode=Pin.OUT)
unused = Pin(11)
spi = SoftSPI(baudrate=3000000, sck=clock, mosi=data, miso=unused)

COLON_LEFT_BOTTOM = 1 << 17 << 16
COLON_LEFT_TOP = 1 << 18 << 16
COLON_RIGHT_BOTTOM = 1 << 17
COLON_RIGHT_TOP = 1 << 18

COLON_LEFT_BOTH = COLON_LEFT_TOP | COLON_LEFT_BOTTOM
COLON_RIGHT_BOTH = COLON_RIGHT_TOP | COLON_RIGHT_BOTTOM
COLON_BOTTOM_BOTH = COLON_LEFT_BOTTOM | COLON_RIGHT_BOTTOM
COLON_TOP_BOTH = COLON_LEFT_TOP | COLON_RIGHT_TOP
COLON_ALL = COLON_LEFT_BOTH | COLON_RIGHT_BOTH

IN15A_MICRO = 0
IN15A_PERCENT = 2
IN15A_PETA = 3
IN15A_KILO = 4
IN15A_MEGA = 5
IN15A_MILLI = 6
IN15A_PLUS = 7
IN15A_MINUS = 8
IN15A_PICO = 9

def clamp(v, lower=-99, upper=99):
    if v > upper:
        return upper
    elif v < lower:
        return lower

def render_digit(j, position=0):
    assert j >= -1 and j <= 9
    if j == -1: j = 10
    return [11, 9, 12, 8, 0, 4, 1, 3, 2, 10, 15][j] << 3 << (position << 3)

def render_digits(*args):
    z = 0
    for position, value in enumerate(reversed(args)):
        z |= render_digit(value, position)
    return z

def render_time(colons=True):
    _, _, _, h, m, s, _, _ = localtime()
    return render_digits(h // 10,  h % 10, m // 10, m % 10, s // 10, s % 10) | (colons and COLON_ALL)

def render_date(colons=True):
    y, m, d, _, _, _, _, _ = localtime()
    return render_digits(y // 10,  y % 10, m // 10, m % 10, d // 10, d % 10) | (colons and COLON_BOTTOM_BOTH)

def render_temperature(t):
    val = abs(clamp(t))
    return render_digits(-1, IN15A_MINUS if t < 0 else -1, val // 10, val % 10, -1, -1) | COLON_RIGHT_TOP

rmt = RMT(0, pin=latch, clock_div=CONFIG_RMT_DIVISOR, idle_level=False)
tim = Timer(0, mode=Timer.PERIODIC)

RMT_DURATION = CONFIG_CPU_FREQUENCY // CONFIG_RMT_DIVISOR // CONFIG_REFRESH_RATE
assert RMT_DURATION <= 32767, "RMT duration %d overflows 32767" % RMT_DURATION

print("Refresh rate: %d Hz" % CONFIG_REFRESH_RATE)
print("PWM period: %d RMT pulses" % RMT_DURATION)

i = 0
d = 0

from time import time, ticks_ms, localtime
z = time()
calibration = 0
while z == time():
    calibration = ticks_ms() % 1000

def is_dst(y, mo, d, h, m):
    if mo < 3 or mo > 11:
        return False
    if 3 < mo < 11:
        return True
    if mo == 3:
        return d >= 8  # Approximation
    if mo == 11:
        return d < 7  # Approximation
    return False

def get_time():
    subsec = (ticks_ms() - calibration) % 1000
    now = time() + CONFIG_TIMEZONE * 3600
    y, mo, d, h, m, s, _, _ = localtime(now)
    if CONFIG_DAYLIGHT_SAVING_ENABLED and is_dst(y, mo, d, h, m):
        now += 3600  # Add 1 hour
        y, mo, d, h, m, s, _, _ = localtime(now)
    return y, mo, d, h, m, s, subsec


def display_static(j):
    spi.write(j.to_bytes(6))
    rmt.write_pulses((1,1), 0)

def display_dimmed(j, brightness=0.5):
    duty = brightness ** CONFIG_DIMMING_GAMMA
    assert brightness >= 0
    assert brightness <= 1
    assert duty >= 0
    assert duty <= 1
    pulses = (1, 100, 1 + int(RMT_DURATION * duty), 1)
    if brightness == 1.0:
        display_static(j)
    else:
        spi.write(j.to_bytes(6))
        rmt.write_pulses(pulses, 0)
        spi.write('\x78\x78\x78\x78\x78\x78')

def display_blended(j, i, progression=0.5):
    assert progression >= 0
    assert progression <= 1
    duty = progression
    pulses = (1, 100, 1 + int(RMT_DURATION * duty), 1)
    if progression == 1.0:
        display_static(j)
    else:
        spi.write(j.to_bytes(6))
        rmt.write_pulses(pulses, 0)
        spi.write(i.to_bytes(6))

STATE_PREVIOUS = 0x787878787878
STATE_REFRESH_MODE = 0

def run_clock(*args):
    global STATE_PREVIOUS
    global STATE_REFRESH_MODE
    y, mo, d, h, m, s, subsec = get_time()
    current = render_digits(h // 10,  h % 10, m // 10, m % 10, s // 10, s % 10)
    prev = STATE_PREVIOUS
    if subsec <= 500:
        current |= COLON_ALL
        prev |= COLON_ALL
    if CONFIG_DIMMING_ENABLED and (h >= CONFIG_DIMMING_START or h < CONFIG_DIMMING_END):
        if STATE_REFRESH_MODE != 1:
            print("Switching to dimming mode, because", CONFIG_DIMMING_START, "<=", h, "<=", CONFIG_DIMMING_END)
            STATE_REFRESH_MODE = 1
        display_dimmed(current, CONFIG_DIMMING_BRIGHTNESS)
    elif CONFIG_BLENDING_ENABLED:
        if STATE_REFRESH_MODE != 2:
            print("Switching to blending mode")
            STATE_REFRESH_MODE = 2
        if subsec <= CONFIG_BLENDING_DURATION:
            if current != prev:
                display_blended(current, prev, progression=subsec / CONFIG_BLENDING_DURATION)
        else:
            display_static(current)
            STATE_PREVIOUS = current
    else:
        display_static(current)

print("Setting up periodic timer at %d Hz (%d ms)" % (CONFIG_REFRESH_RATE, 1000 // CONFIG_REFRESH_RATE))
tim.init(mode=Timer.PERIODIC, period=1000 // CONFIG_REFRESH_RATE, callback=run_clock)
