import gc
import network
import picoweb
import json
from time import sleep_ms
from timezone import TIMEZONES

app = picoweb.WebApp(__name__)
ap_if = network.WLAN(network.AP_IF)
sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)
nets = sta_if.scan()
config = dict()
try:
    with open("config.json") as fh:
        config = json.loads(fh.read())
        sta_if.connect(config.get("ssid"), config.get("password"))
except OSError:
    pass

print("Scanning for wireless networks...")

@app.route("/connect")
def index(req, resp):
    if req.method == "POST":
        yield from req.read_form_data()
    else:
        req.parse_qs()
    yield from picoweb.start_response(resp)
    with open("config.json", "w") as fh:
        fh.write(json.dumps(req.form))
    yield from resp.awrite("Setting saved please power cycle device")


@app.route("/")
def index(req, resp):
    print("Serving index")
    yield from picoweb.start_response(resp)
    yield from resp.awrite("<html>")
    yield from resp.awrite("<head>")
    yield from resp.awrite("<meta name='viewport' content='width=device-width, initial-scale=1'>")
    yield from resp.awrite("</head>")
    yield from resp.awrite("<body>")
    yield from resp.awrite("<h>Welcome to NixiESP12 configuration wizard</h>")
    yield from resp.awrite("<p>Detected wireless networks:</p>")
    yield from resp.awrite("<form action='/connect' method='post'>")
    yield from resp.awrite("<p>Select wireless network:</p>")
    yield from resp.awrite("<select name='ssid'>")
    for ssid, _, _, snr, crypto, _ in nets:
        ssid = ssid.decode("utf-8")
        yield from resp.awrite("<option>" + ssid + "</option>")
    yield from resp.awrite("</select>")
    yield from resp.awrite("<p>Wireless password is applicable:</p>")
    yield from resp.awrite("<input type='password' name='password'/>")
    yield from resp.awrite("<p>Timezone:</p>")
    yield from resp.awrite("<select name='timezone'>")
    for index, (dst, offset, title) in enumerate(TIMEZONES):
        yield from resp.awrite("<option value='%d'>%s</option>" % (index, title))
    yield from resp.awrite("</select>")
    yield from resp.awrite("<p>NTP resynchronization interval:</p>")
    yield from resp.awrite("<select name='interval'>")
    for j in range(0, 73):
        yield from resp.awrite("<option value='%d'>%d hours</option>" % (j*3600, j))
    yield from resp.awrite("</select>")
    yield from resp.awrite("<p>&nbsp;</p>")
    yield from resp.awrite("<input type='submit'/>")
    yield from resp.awrite("</form>")
    yield from resp.awrite("</body>")
    yield from resp.awrite("<html>")

timed_out = True
if config:
    print("Connecting to", config.get("ssid"))
    for j in range(0,30):
        if sta_if.isconnected():
            ap_if.active(False)
            timed_out = False
            break
        sleep_ms(200)

if timed_out:
    ap_if.active(True)
    print("Starting setup wizard on", ap_if.ifconfig())
    app.run()


TIMEZONE = TIMEZONES[int(config.get("timezone", 30))][1]
print("Using timezone", TIMEZONES[int(config.get("timezone", 30))])
RESYNC = int(config.get("interval")) # Resync once in 8 hours
print("NTP resynchronization interval", RESYNC, "seconds")
DEBUG = False

print("Press Ctrl-C now to abort main.py execution and retain keyboard input")
sleep_ms(2000)

import time
import ntptime
from machine import Pin, Timer

# Note that keyboard input is lost beyond this point!
clock = Pin(3, mode=Pin.OUT)
latch = Pin(0, mode=Pin.OUT)
data = Pin(2, mode=Pin.OUT)
blink = False
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

def dst_offset(month, day, dow):
    if month < 3 or month > 10:
        return 0
    if month > 3 and month < 10:
        return 1
    previous_sunday = day - dow
    if month == 3:
        return int(previous_sunday >= 25)
    return int(previous_sunday < 25)


def dump_time(year, month, day, hour, minute, second, dow):
    offset = dst_offset(month, day, dow)
    if DEBUG:
        print("Time is %02d:%02d:%02d, dst offset %d" % (hour, minute, second, offset))
    hour = (hour + TIMEZONE + offset) % 24
    bitbang_digit(hour // 10)
    bitbang_digit(hour % 10)
    bitbang_digit(minute // 10)
    bitbang_digit(minute % 10)
    bitbang_digit(second // 10)
    bitbang_digit(second % 10)

# RTC accuracy is still garbage, time.ticks_ms() which is bound to CPU ticks seems to be more accurate
# https://forum.micropython.org/viewtopic.php?t=3251#p19092


# Boot up test sequence
for j in range(0, 10):
    for i in range(0, 6):
        bitbang_digit(j)
    latch.on()
    latch.off()
    sleep_ms(500)


while True:
    if countdown <= 0:
        try:
            ticks_then, time_then = time.ticks_ms(), ntptime.time()
        except OSError:
            sleep_ms(500)
            print("Resync failed")
            continue
        else:
            countdown = RESYNC
            print("Resync done")
    else:
        year, month, day, hour, minute, second, dow, _ = time.localtime(time_then + (time.ticks_ms() - ticks_then) // 1000)
        sleep_ms(500-(time.ticks_ms() - ticks_then) % 1000)
        blink = True
        dump_time(year, month, day, hour, minute, second, dow)
        latch.on()
        latch.off()
        countdown -= 1

    year, month, day, hour, minute, second, dow, _ = time.localtime(time_then + (time.ticks_ms() - ticks_then) // 1000)
    sleep_ms(1001-(time.ticks_ms() - ticks_then) % 1000)
    blink = False
    dump_time(year, month, day, hour, minute, second, dow)
    latch.on()
    latch.off()

main()
