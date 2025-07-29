# Arduino variant for ESP8266

This firmware is designed for Nixie tube clocks using the ESP8266 microcontroller.

## Features

- WiFi configuration via captive portal (WiFiManager)
- NTP time synchronization
- Time and date display
- Timezone and NTP server configuration
- Clock drift mitigation using the ezTime library

## Note

The main issue with ESP8266-based clocks is clock drift. This firmware uses the ezTime library to reduce drift, but accuracy is still limited compared to ESP32-based