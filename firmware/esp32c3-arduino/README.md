# Arduino variant for ESP8266

This firmware is designed to run on the [LilyGO T-01C3](https://lilygo.cc/products/t-01c3?srsltid=AfmBOopddAvO0gTIFNYZyTcoF1PxQjxZ0YAxuhoQviz9i5j4B0WOdg4l) board and serves as a drop-in replacement for the original ESP8266-based Nixie clock firmware

This firmware features a high refresh rate display with advanced dimming and blending effects, leveraging the ESP32's RMT (Remote Control) peripheral for precise timing and smooth transitions

## Highlights

- **High Refresh Rate:** Achieves smooth digit transitions and flicker-free display using RMT hardware
- **Dimming & Blending:** Configurable dimming and blending for night mode and digit transitions
- **WiFiManager Configuration:** Easily configure all clock options via a web portal
- **Prometheus Metrics:** Exposes runtime and system metrics for monitoring

## Configuration Options via WiFiManager

- **NTP Time Server:** Set the network time server for clock synchronization
- **City:** Select your city for timezone presets
- **Timezone:** Manually specify the POSIX timezone string
- **Display Mode:** Choose between time, date, or alternating time/date display
- **Dimming Duty Cycle:** Adjust brightness for night mode
- **Dimming Start/End:** Set hours for automatic dimming
- **Blending Duration:** Control the duration of digit blending transitions
- **Hour Format:** Select 12-hour or 24-hour display

## Prometheus Metrics

The firmware exposes the following metrics for monitoring:

- `nixie_boot_timestamp_seconds`: Boot time of the device
- `nixie_last_ntp_sync_timestamp_seconds`: Last successful NTP synchronization
- `nixie_littlefs_total_bytes`: Total LittleFS storage size
- `nixie_littlefs_used_bytes`: Used LittleFS storage
- `nixie_uptime_seconds`: Device uptime
- `nixie_display_task_iterations_total`: Number of display task iterations
- `nixie_ntp_sync_count_total`: Number of NTP sync events
- `nixie_wifi_manager_process_count_total`: Number of WiFiManager process events

## Advanced Features

- **Automatic NTP Sync:** Periodically synchronizes time with the configured NTP server
- **Stale NTP Detection:** Blinks all digits and colons if NTP sync is stale
- **Critical Section Display Updates:** Uses FreeRTOS and portMUX for safe, high-speed display updates

## Getting Started

1. Flash the firmware to your ESP32-C3
2. Connect to the WiFiManager AP (SSID is based on device MAC)
3. Configure your clock settings via the web portal
4. Monitor metrics via Prometheus-compatible tools

---

For more details, see the source code and comments.