
import ntptime
import esp
from time import sleep, localtime
from machine import Pin, Timer

TIMEZONE = 3
RESYNC = 7200 # Resync once in two hours

print("Press Ctrl-C now abort main.py execution and to retain keyboard input")
sleep(1)

# Configure powersave
esp.sleep_type(esp.SLEEP_LIGHT)

# Note that keyboard input is lost beyond this point!
clock = Pin(3, mode=Pin.OUT)
latch = Pin(0, mode=Pin.OUT)
data = Pin(2, mode=Pin.OUT)
blink = 0
lookup = 11, 9, 12, 8, 0, 4, 1, 3, 2, 10
countdown = 0

def bitbang_bit(value):
    if value & 1:
        data.on()
    else:
        data.off()
    clock.on()
    clock.off()

def bitbang_digit(digit):
    bitbang_bit(blink)
    for i in range(0,4):
        bitbang_bit(lookup[digit] << i >> 3)
    bitbang_bit(blink)
    bitbang_bit(blink)
    bitbang_bit(blink)

timer = Timer(-1)

def schedule(delay=0):
    global countdown
    if countdown <= 0:
        ntptime.settime()
        countdown = RESYNC
        print("Resync")
    countdown -= 1
    if delay:
        timer.init(period=1000, mode=Timer.ONE_SHOT, callback=dump)
    else:
        dump()

def dump_time(hour, minute, second):
    print("Time is %02d:%02d:%02d" % (hour, minute, second))
    bitbang_digit(hour // 10)
    bitbang_digit(hour % 10)
    bitbang_digit(minute // 10)
    bitbang_digit(minute % 10)
    bitbang_digit(second // 10)
    bitbang_digit(second % 10)

def dump(t=None):
    global blink
    year, month, day, hour, minute, second, _, millis = localtime()
    dump_time((hour + TIMEZONE) % 24, minute, second)
    latch.on()
    latch.off()
    blink = 1-blink
    schedule(1000-millis)

schedule()
