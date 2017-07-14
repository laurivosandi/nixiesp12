# Just in case prevent boot loops
from time import sleep
print("Press Ctrl-C to stop boot script...")
sleep(1)

# Connect to wireless network as client
import network
sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)
sta_if.connect("Robootikaklubi", "u4HNj3sgYK")

# Synchronize clock
import ntptime
ntptime.settime()

# Clean up
import gc
gc.collect()
