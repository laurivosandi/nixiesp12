
# Disable AP
import network
ap_if = network.WLAN(network.AP_IF)
ap_if.active(False)
print("Access point disabled")

# Connect to wireless network as client
sta_if = network.WLAN(network.STA_IF)
sta_if.active(True)
sta_if.connect("Robootikaklubi", "u4HNj3sgYK")
while not sta_if.isconnected():
    pass

# Clean up
import gc
gc.collect()
