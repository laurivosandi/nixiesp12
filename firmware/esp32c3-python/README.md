# MicroPython variant for ESP32C3

This firmware is designed to run on ESP32-C3 boards using MicroPython. It drives a Nixie tube clock with high refresh rate, advanced dimming, and blending effects, leveraging the ESP32's RMT peripheral for precise timing

## Highlights

- **High Refresh Rate:** Smooth, flicker-free display using RMT hardware
- **Dimming & Blending:** Configurable night mode brightness and digit blending transitions
- **Configurable via `config.py`:** All major settings can be overridden by uploading a `config.py` file
- **NTP Synchronization:** Periodically syncs time with NTP servers
- **Timezone & DST Support:** Adjustable timezone and daylight saving settings

## Configuration Options

You can override any of these defaults by uploading a `config.py` file:

- `CONFIG_TIMEZONE`: Timezone offset from UTC (default: 2)
- `CONFIG_DAYLIGHT_SAVING_ENABLED`: Enable/disable DST (default: True)
- `CONFIG_NTP_SYNC_INTERVAL_HOURS`: NTP sync interval (default: 24)
- `CONFIG_DIMMING_ENABLED`: Enable night dimming (default: True)
- `CONFIG_DIMMING_BRIGHTNESS`: Night brightness (default: 0.4)
- `CONFIG_DIMMING_START`: Dimming start hour (default: 15)
- `CONFIG_DIMMING_END`: Dimming end hour (default: 6)
- `CONFIG_DIMMING_GAMMA`: Dimming gamma correction (default: 2.2)
- `CONFIG_BLENDING_ENABLED`: Enable digit blending (default: True)
- `CONFIG_BLENDING_DURATION`: Blending duration in ms (default: 150)
- `CONFIG_NETWORKS`: Dictionary of SSIDs and passwords for auto-connect

## Features

- **WiFi Auto-Connect:** Scans and connects to known networks
- **NTP Time Sync:** Sets system time via NTP after WiFi connection
- **Display Modes:** Time, date, and temperature rendering functions
- **RMT-Based Display:** Uses ESP32 RMT for precise display timing
- **Night Mode:** Automatic dimming based on configured hours
- **Blending:** Smooth digit transitions for improved aesthetics

## Usage

1. Flash MicroPython to your ESP32-C3 board
2. Upload `main.py` and (optionally) `config.py` to the device
3. Reboot the board. The clock will auto-connect to WiFi, sync time, and start displaying

## Notes

- The firmware is intended for advanced users familiar with MicroPython and ESP32 hardware
- For custom settings, create and upload a `config.py` file with your overrides
- RMT and SPI pin assignments are set for typical Nixie clock hardware; adjust as needed for your build

---

For more details, see the source code and
