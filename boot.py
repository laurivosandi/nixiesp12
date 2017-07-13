# Just in case prevent boot loops
from time import sleep
print("Press Ctrl-C to stop boot script...")
sleep(1)

# Connect to wireless network as client
import network
sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)
sta_if.connect("Robootikaklubi", "u4HNj3sgYK")
print("Copy paste following to WebREPL client:")
print("ws://%s:8266/" % sta_if.ifconfig()[0])

# Synchronize clock
import ntptime
ntptime.settime()

# Start WebREPL server
import webrepl
webrepl.start(password="salakala")

# Derive hostname
import ubinascii
MAC_SUFFIX=ubinascii.hexlify(sta_if.config("mac")[-3:])
HOSTNAME="ESP_%s" % MAC_SUFFIX.decode("ascii").upper()

# Perform HTTP POST request
#import urequests
#urequests.post("http://sumo.koodur.com/pub/", data=HOSTNAME)

# Clean up
import gc
gc.collect()
