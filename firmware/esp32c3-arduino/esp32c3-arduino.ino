#include <Arduino.h>
#include <WiFiManager.h>
#include <WiFi.h>
#include "esp_sntp.h"
#include <time.h>
#include <math.h>
#include <driver/rmt.h>
#include "cities.h"
#include <LittleFS.h>

// --- Configuration ---
#define CONFIG_CPU_FREQUENCY 80000000
#define CONFIG_RMT_DIVISOR 50
#define CONFIG_REFRESH_RATE 50
#define REFRESH_CYCLE CONFIG_CPU_FREQUENCY / CONFIG_RMT_DIVISOR / CONFIG_REFRESH_RATE - 100

static_assert(REFRESH_CYCLE > 0, "REFRESH_CYCLE must be > 0");
static_assert(REFRESH_CYCLE < 32768, "REFRESH_CYCLE must be < 32768");


// --- Pin Definitions ---
#define PIN_CLOCK 20
#define PIN_LATCH 9
#define PIN_DATA 2
#define PIN_UNUSED 11

// --- Colon and Symbol Definitions ---
#define COLON_LEFT_BOTTOM (1ULL << (17 + 16))
#define COLON_LEFT_TOP (1ULL << (18 + 16))
#define COLON_RIGHT_BOTTOM (1ULL << 17)
#define COLON_RIGHT_TOP (1ULL << 18)

#define COLON_LEFT_BOTH (COLON_LEFT_TOP | COLON_LEFT_BOTTOM)
#define COLON_RIGHT_BOTH (COLON_RIGHT_TOP | COLON_RIGHT_BOTTOM)
#define COLON_BOTTOM_BOTH (COLON_LEFT_BOTTOM | COLON_RIGHT_BOTTOM)
#define COLON_TOP_BOTH (COLON_LEFT_TOP | COLON_RIGHT_TOP)
#define COLON_ALL (COLON_LEFT_BOTH | COLON_RIGHT_BOTH)

#define IN15A_MICRO 0
#define IN15A_PERCENT 2
#define IN15A_PETA 3
#define IN15A_KILO 4
#define IN15A_MEGA 5
#define IN15A_MILLI 6
#define IN15A_PLUS 7
#define IN15A_MINUS 8
#define IN15A_PICO 9


#define NTP_SYNC_TIMEOUT_SECONDS 8*3600

int configDimmingDutyCycle = 0;
int configDimmingStart = 0;
int configDimmingEnd = 0;
int configHourFormat = 12;

int current_dimming_duty_cycle;
enum typeOperationMode {
  OPERATION_MODE_NORMAL,
  OPERATION_MODE_DIMMED,
} operationModeCurrent = OPERATION_MODE_NORMAL;

#define DISPLAY_MODE_TIME 1
#define DISPLAY_MODE_DATE 2
#define DISPLAY_MODE_DATETIME 3

int configDisplayModesEnabled = 1;
int displayModeCurrent = 1;

WiFiManager wm;

const char displayModesCombobox[] = R"(
<br/>
<label for="displayModeCombobox">Clock display format</label>
<select name="timeDisplay" id="displayModeCombobox" onchange="document.getElementById('displayMode').value = this.value">
  <option value="1">Time</option>
  <option value="2">Date</option>
  <option value="3">Time and Date</option>
</select>
<script>
  document.getElementById("displayModeCombobox").value = document.getElementById("displayMode").value;
  document.querySelector("[for='displayMode']").hidden = true;
  document.getElementById("displayMode").hidden = true;
</script>)";


WiFiManagerParameter paramNetworkTimeServer("networkTimeServer", "Network time server", "ee.pool.ntp.org", 63);
WiFiManagerParameter paramDisplayMode("displayMode", "Will be hidden", "1", 2);
WiFiManagerParameter paramDisplayModeCombobox(displayModesCombobox);
WiFiManagerParameter paramCity(cities);
WiFiManagerParameter paramTimezone("timezone", "Timezone encoding", "EET-2EEST,M3.5.0/3,M10.5.0/4", 30);
#define CONFIG_TIMEZONE "EET-2EEST,M3.5.0/3,M10.5.0/4" // Estonia, adjust as needed

const char dimmerSliderSnippet[] = R"(
<br/><label for='dimming_duty_cycle_slider'>Night time dimming duty cycle (%)</label>
<input type="range" min="500" max="32767" value="1000" class="slider" id="dimming_duty_cycle_slider" onchange="document.getElementById('dimming_duty_cycle').value = this.value">
<script>
document.getElementById('dimming_duty_cycle').hidden = true;
</script>
)";
WiFiManagerParameter paramDimmingDutyCycle("dimming_duty_cycle", "", "1000", 6);
WiFiManagerParameter paramDimmingDutyCycleSlider(dimmerSliderSnippet);

time_t bootTimestamp = 0;
time_t lastNtpSyncTimestamp = 0;


// Dimmer settings
volatile long displayInterruptCount = 0;

const char blendingSliderSnippet[] = R"(
<br/><label for='blending_duration_slider'>Blending duration (0 .. 400ms)</label>
<input type='range' min='0' max='400' value='200' class='slider' id='blending_duration_slider' onchange="document.getElementById('blending_duration').value = this.value">
<script>
document.getElementById('blending_duration').hidden = true;
</script>
)";
WiFiManagerParameter paramBlendingDuration("blending_duration", "", "200", 4);
WiFiManagerParameter paramBlendingDurationSlider(blendingSliderSnippet);


const char dimmingStartCombobox[] = R"(
<br/>
<label for='dimming_start_hour'>Night time dimming start time</label>
<select name='dimming_start' id='dimming_start_hour' onchange="document.getElementById('dimming_start').value = this.value">
  <option value='13'>13:00</option>
  <option value='14'>14:00</option>
  <option value='15'>15:00</option>
  <option value='16'>16:00</option>
  <option value='17'>17:00</option>
  <option value='18'>18:00</option>
  <option value='19'>19:00</option>
  <option value='20'>20:00</option>
  <option value='21'>21:00</option>
  <option value='22'>22:00</option>
  <option value='23'>23:00</option>
</select>
<script>
document.getElementById('dimming_start_hour').value = "22";
document.getElementById('dimming_start').hidden = true;
</script>
)";

const char dimmingEndCombobox[] = R"(
<br/>
<label for='dimming_end_hour'>Night time dimming end time</label>
<select name='dimming_end' id='dimming_end_hour' onchange="document.getElementById('dimming_end').value = this.value">
  <option value='4'>4:00</option>
  <option value='5'>5:00</option>
  <option value='6'>6:00</option>
  <option value='7'>7:00</option>
  <option value='8'>8:00</option>
  <option value='9'>9:00</option>
  <option value='10'>10:00</option>
  <option value='11'>11:00</option>
  <option value='12'>12:00</option>
</select>
<script>
document.getElementById('dimming_end_hour').value = "6";
document.getElementById('dimming_end').hidden = true;
</script>
)";

const char hourFormatCombobox[] = R"(
<br/>
<label for="hourFormatCombobox">Hour format</label>
<select name="hour_format" id="hourFormatCombobox" onchange="document.getElementById('hour_format').value = this.value">
  <option value="24">24-hour</option>
  <option value="12">12-hour</option>
</select>
<script>
  document.getElementById("hourFormatCombobox").value = "12";
  document.getElementById("hour_format").hidden = true;
</script>
)";

WiFiManagerParameter paramHourFormat("hour_format", "", "12", 3);
WiFiManagerParameter paramHourFormatCombobox(hourFormatCombobox);
WiFiManagerParameter paramDimmingStart("dimming_start", "", "22", 3);
WiFiManagerParameter paramDimmingStartCombobox(dimmingStartCombobox);
WiFiManagerParameter paramDimmingEnd("dimming_end", "", "6", 3);
WiFiManagerParameter paramDimmingEndCombobox(dimmingEndCombobox);

// --- NTP Sync Counter ---
volatile unsigned long displayTaskIterationsCount = 0;
volatile unsigned long configBlendingDuration = 0;
volatile unsigned long ntpSyncCount = 0;
volatile unsigned long wifiManagerProcessCount = 0;

void IRAM_ATTR timeavailable(struct timeval *t) {
    ntpSyncCount++;
    if (bootTimestamp == 0 && t) {
        bootTimestamp = t->tv_sec;
    }
    if (t) {
        lastNtpSyncTimestamp = t->tv_sec;
    }
}

#define RMT_TX_GPIO 9


// --- State ---
uint64_t STATE_PREVIOUS = 0x787878787878ULL;
int STATE_REFRESH_MODE = 0;

// --- Helper Functions ---
void spi_write_bytes(const uint8_t* data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        uint8_t b = data[i];
        for (int bit = 7; bit >= 0; bit--) {
            digitalWrite(PIN_CLOCK, LOW);
            digitalWrite(PIN_DATA, (b >> bit) & 1);
            digitalWrite(PIN_CLOCK, HIGH);
        }
    }
}

int clamp(int v, int lower = -99, int upper = 99) {
    if (v > upper) return upper;
    if (v < lower) return lower;
    return v;
}

uint64_t render_digit(int j, int position = 0) {
    static const int table[11] = {11, 9, 12, 8, 0, 4, 1, 3, 2, 10, 15};
    if (j < -1 || j > 9) j = 10;
    if (j == -1) j = 10;
    return ((uint64_t)table[j] << 3) << (position * 8);
}

uint64_t render_digits(int d5, int d4, int d3, int d2, int d1, int d0) {
    uint64_t z = 0;
    int vals[6] = {d0, d1, d2, d3, d4, d5};
    for (int position = 0; position < 6; position++) {
        z |= render_digit(vals[position], position);
    }
    return z;
}

uint64_t render_time(bool colons = true) {
    struct tm timeinfo;
    time_t now = time(nullptr);
    localtime_r(&now, &timeinfo);
    int h = timeinfo.tm_hour % configHourFormat;
    int m = timeinfo.tm_min;
    int s = timeinfo.tm_sec;
    return render_digits(h / 10, h % 10, m / 10, m % 10, s / 10, s % 10) | (colons ? COLON_ALL : 0);
}

uint64_t render_date(bool colons = true) {
    struct tm timeinfo;
    time_t now = time(nullptr);
    localtime_r(&now, &timeinfo);
    int y = timeinfo.tm_year % 100;
    int m = timeinfo.tm_mon + 1;
    int d = timeinfo.tm_mday;
    return render_digits(y / 10, y % 10, m / 10, m % 10, d / 10, d % 10) | (colons ? COLON_BOTTOM_BOTH : 0);
}

uint64_t render_temperature(int t) {
    int val = abs(clamp(t));
    return render_digits(-1, t < 0 ? IN15A_MINUS : -1, val / 10, val % 10, -1, -1) | COLON_RIGHT_TOP;
}

void rmt_pulse(uint32_t duration) {
    rmt_data_t items[3];
    items[0].level0 = 1; items[0].duration0 = 1; // latch immediately
    items[0].level1 = 0; items[0].duration1 = duration;
    items[1].level0 = 1; items[1].duration0 = 1;
    items[1].level1 = 0; items[1].duration1 = 1;
    rmtWriteAsync(RMT_TX_GPIO, items, duration == 0 ? 1 : 2);
}

void display_static(uint64_t value) {
    uint8_t bytes[6];
    for (int i = 0; i < 6; i++) bytes[i] = (value >> (8 * (5 - i))) & 0xFF;
    spi_write_bytes(bytes, 6);
    rmt_data_t items[1];
    items[0].level0 = 1; items[0].duration0 = 1;
    items[0].level1 = 0; items[0].duration1 = 1;
    rmtWrite(RMT_TX_GPIO, items, 1, RMT_WAIT_FOR_EVER);
}

void display_dimmed(uint64_t value, int duty) {
    uint8_t bytes[6];
    for (int i = 0; i < 6; i++) bytes[i] = (value >> (8 * (5 - i))) & 0xFF;
    if (duty >= 32767) {
        display_static(value);
    } else {
        spi_write_bytes(bytes, 6);
        rmt_pulse(duty);
        uint8_t blank[6] = {0x78, 0x78, 0x78, 0x78, 0x78, 0x78};
        spi_write_bytes(blank, 6);
    }
}

void display_blended(uint64_t value, uint64_t prev, float progression) {
    int duty = 32767 * progression;
    if (duty < 500) { duty = 500; }
    uint8_t bytes[6], prev_bytes[6];
    for (int i = 0; i < 6; i++) {
        bytes[i] = (value >> (8 * (5 - i))) & 0xFF;
        prev_bytes[i] = (prev >> (8 * (5 - i))) & 0xFF;
    }
    if (progression >= 1.0) {
        display_static(value);
    } else {
        spi_write_bytes(bytes, 6);
        rmt_pulse(duty);
        spi_write_bytes(prev_bytes, 6);
    }
}

bool isNtpStale() {
    time_t now = time(nullptr);
    return (lastNtpSyncTimestamp == 0) || (now - lastNtpSyncTimestamp > NTP_SYNC_TIMEOUT_SECONDS);
}

void handleMetrics(){
    String buf = "";


    buf += "nixie_sketch_size_bytes ";
    buf += ESP.getSketchSize();
    buf += "\n";

    buf += "nixie_flash_space_bytes ";
    buf += ESP.getFlashChipSize();
    buf += "\n";

    buf += "nixie_free_heap_bytes ";
    buf += ESP.getFreeHeap();
    buf += "\n";

    buf += "nixie_min_free_heap_bytes ";
    buf += ESP.getMinFreeHeap();
    buf += "\n";

    buf += "nixie_cpu_frequency_mhz ";
    buf += getCpuFrequencyMhz();
    buf += "\n";

    buf += "nixie_task_count ";
    buf += uxTaskGetNumberOfTasks();
    buf += "\n";

    buf += "nixie_wifi_rssi_dbm ";
    buf += WiFi.RSSI();
    buf += "\n";

    buf += "nixie_wifi_channel ";
    buf += WiFi.channel();
    buf += "\n";

    int wifiStatus = WiFi.status();
    const char* wifiStatusStr = "UNKNOWN";
    switch (wifiStatus) {
        case WL_IDLE_STATUS: wifiStatusStr = "IDLE"; break;
        case WL_NO_SSID_AVAIL: wifiStatusStr = "NO_SSID_AVAIL"; break;
        case WL_SCAN_COMPLETED: wifiStatusStr = "SCAN_COMPLETED"; break;
        case WL_CONNECTED: wifiStatusStr = "CONNECTED"; break;
        case WL_CONNECT_FAILED: wifiStatusStr = "CONNECT_FAILED"; break;
        case WL_CONNECTION_LOST: wifiStatusStr = "CONNECTION_LOST"; break;
        case WL_DISCONNECTED: wifiStatusStr = "DISCONNECTED"; break;
    }
    buf += "nixie_wifi_status_info{status=\"";
    buf += wifiStatusStr;
    buf += "\"} ";
    buf += wifiStatus;
    buf += "\n";

    buf += "nixie_wifi_info{ssid=\"";
    buf += WiFi.SSID();
    buf += "\",bssid=\"";
    buf += WiFi.BSSIDstr();
    buf += "\",ip=\"";
    buf += WiFi.localIP().toString();
    buf += "\",gateway=\"";
    buf += WiFi.gatewayIP().toString();
    buf += "\",dns=\"";
    buf += WiFi.dnsIP().toString();
    buf += "\"} 1\n";

    buf += "nixie_ntp_sync_count ";
    buf += ntpSyncCount;
    buf += "\n";

    buf += "nixie_wifi_manager_process_count ";
    buf += wifiManagerProcessCount;
    buf += "\n";

    buf += "nixie_task_stack_high_water_mark_bytes ";
    buf += uxTaskGetStackHighWaterMark(NULL);
    buf += "\n";

    buf += "nixie_display_task_iterations_count ";
    buf += displayTaskIterationsCount;
    buf += "\n";

    if (bootTimestamp > 0) {
        buf += "nixie_boot_timestamp_seconds ";
        buf += bootTimestamp;
        buf += "\n";
    }

    buf += "nixie_last_ntp_sync_timestamp_seconds ";
    buf += lastNtpSyncTimestamp;
    buf += "\n";

    buf += "nixie_littlefs_total_bytes ";
    buf += LittleFS.totalBytes();
    buf += "\n";

    buf += "nixie_littlefs_used_bytes ";
    buf += LittleFS.usedBytes();
    buf += "\n";

    wm.server->send(200, "text/plain", buf);
}

unsigned char timeserver[63] = {'\0'};
unsigned char timezone[30] = {'\0'};
bool ntp_started = false;

int loadClockConfig() {
  File file = LittleFS.open("/timezone", "r");
  if (!file) { return 1; }
  if (!file.read(timezone, sizeof(timezone))) { return 2; }

  file = LittleFS.open("/timeserver", "r");
  if (!file) { return 3; }
  if (!file.read(timeserver, sizeof(timeserver))) { return 4; }

  if (!ntp_started) {
    Serial.print("Using time server: ");
    Serial.println((const char*)timeserver);
    configTime(0, 0, (const char*)timeserver);
    ntp_started = true;
  } else {
    Serial.print("NTP already started, reset to apply new time server");

  }

  Serial.print("Using timezone: ");
  Serial.println((const char*)timezone);
  setenv("TZ", (const char*)timezone, 1);
  tzset();


  unsigned char modes[1] = {'\0'};
  file = LittleFS.open("/modes", "r");
  if (!file) { return 5; }
  if (!file.read(modes, sizeof(modes))) { return 6; }
  displayModeCurrent = atoi((const char*)modes);
  Serial.print("Enabled display modes:");
  if (displayModeCurrent & DISPLAY_MODE_DATE) {
    Serial.print(" DATE");
  }
  if (displayModeCurrent & DISPLAY_MODE_TIME) {
    Serial.print(" TIME");
  }
  Serial.println();

  unsigned char bufDimming[10] = {'\0'};
  file = LittleFS.open("/dimming", "r");
  if (!file) { return 7; }
  if (!file.read(bufDimming, sizeof(bufDimming))) { return 8; }
  configDimmingDutyCycle = atoi((const char*)bufDimming); // ensure integer
  Serial.print("Night time dimming duty cycle: ");
  Serial.println(configDimmingDutyCycle);

  unsigned char bufBlending[10] = {'\0'};
  file = LittleFS.open("/blending_duration", "r");
  if (file && file.read(bufBlending, sizeof(bufBlending))) {
      configBlendingDuration = atoi((const char*)bufBlending);
      Serial.print("Blending duration (ms): ");
      Serial.println(configBlendingDuration);
  }

  unsigned char bufDimmingStart[4] = {'\0'};
  file = LittleFS.open("/dimming_start", "r");
  if (file && file.read(bufDimmingStart, sizeof(bufDimmingStart))) {
    configDimmingStart = atoi((const char*)bufDimmingStart);
    Serial.print("Dimming start hour: ");
    Serial.println(configDimmingStart);
  }

  unsigned char bufDimmingEnd[4] = {'\0'};
  file = LittleFS.open("/dimming_end", "r");
  if (file && file.read(bufDimmingEnd, sizeof(bufDimmingEnd))) {
    configDimmingEnd = atoi((const char*)bufDimmingEnd);
    Serial.print("Dimming end hour: ");
    Serial.println(configDimmingEnd);
  }

  unsigned char bufHourFormat[4] = {'\0'};
  file = LittleFS.open("/hour_format", "r");
  if (file && file.read(bufHourFormat, sizeof(bufHourFormat))) {
        configHourFormat = atoi((const char*)bufHourFormat); // 12 or 24
        Serial.print("Hour format: ");
        Serial.println(configHourFormat);
    } else {
        configHourFormat = 12; // default
    }

  return 0;
}

void saveParamsCallback() {
    File file = LittleFS.open("/timezone", "w");
    Serial.println("Saving timezone: " + String(paramTimezone.getValue()));
    file.print(paramTimezone.getValue());
    file.close();

    file = LittleFS.open("/dimming", "w");
    Serial.println("Saving dimming duty cycle: " + String(paramDimmingDutyCycle.getValue()));
    file.print(paramDimmingDutyCycle.getValue()); // save as integer string
    file.close();
    configDimmingDutyCycle = atoi(paramDimmingDutyCycle.getValue()); // update runtime value

    file = LittleFS.open("/modes", "w");
    file.print(paramDisplayMode.getValue());
    file.close();

    file = LittleFS.open("/blending_duration", "w");
    file.print(paramBlendingDuration.getValue());
    file.close();
    configBlendingDuration = atoi(paramBlendingDuration.getValue());

    file = LittleFS.open("/dimming_start", "w");
    file.print(paramDimmingStart.getValue());
    file.close();
    configDimmingStart = atoi(paramDimmingStart.getValue());

    file = LittleFS.open("/dimming_end", "w");
    file.print(paramDimmingEnd.getValue());
    file.close();
    configDimmingEnd = atoi(paramDimmingEnd.getValue());

    file = LittleFS.open("/timeserver", "w");
    Serial.println("Saving timeserver: " + String(paramNetworkTimeServer.getValue()));
    file.print(paramNetworkTimeServer.getValue());
    file.close();

    file = LittleFS.open("/hour_format", "w");
    Serial.println("Saving hour format: " + String(paramHourFormat.getValue()));
    file.print(paramHourFormat.getValue());
    file.close();
    configHourFormat = atoi(paramHourFormat.getValue());

    loadClockConfig();
}



portMUX_TYPE displayMux = portMUX_INITIALIZER_UNLOCKED;
int calibration = 0;
int ps = 0;

void DisplayTask(void *pvParameters) {
    const TickType_t interval = pdMS_TO_TICKS(1000 / CONFIG_REFRESH_RATE);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;) {
        struct tm timeinfo;
        time_t now = time(nullptr);
        localtime_r(&now, &timeinfo);

        int h = timeinfo.tm_hour;
        int m = timeinfo.tm_min;
        int s = timeinfo.tm_sec;

        int subsec = millis() % 1000;

        // At second change calibrate CPU milliseconds offset
        if (ps != 0 && s != ps) {
            calibration = subsec;

            // Print date, time, seconds since last NTP sync, display mode, rendering mode
            struct tm timeinfo;
            time_t now = time(nullptr);
            localtime_r(&now, &timeinfo);

            Serial.printf("%04d-%02d-%02d ", timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday);
            Serial.printf("%02d:%02d:%02d ", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

            Serial.print("Seconds since last NTP sync: ");
            Serial.print(now - lastNtpSyncTimestamp); Serial.print(" ");

            Serial.print("Display mode: ");
            bool showing_date = false;
            if (displayModeCurrent == DISPLAY_MODE_DATE) {
                Serial.print("DATE ");
                showing_date = true;
            } else if (displayModeCurrent == DISPLAY_MODE_DATETIME) {
                if ((now % 20) >= 10) {
                    Serial.print("DATE ");
                    showing_date = true;
                } else {
                    Serial.print("TIME ");
                }
            } else {
                Serial.print("TIME ");
            }

            Serial.print("Rendering mode: ");
            if (configDimmingDutyCycle < 32767 && (timeinfo.tm_hour >= configDimmingStart || timeinfo.tm_hour < configDimmingEnd)) {
                Serial.print("DIMMING");
            } else if (configBlendingDuration > 0) {
                Serial.print("BLENDING");
            } else {
                Serial.print("STATIC");
            }
            Serial.println();
        }
        ps = s;

        subsec = (1000 + subsec - calibration) % 1000;

        uint64_t current = 0;
        uint64_t prev = STATE_PREVIOUS;

        // Select display mode
        switch (displayModeCurrent) {
            case DISPLAY_MODE_DATE:
                current = render_date();
                break;
            case DISPLAY_MODE_DATETIME: {
                // Alternate every 10 seconds between time and date
                time_t now = time(nullptr);
                if ((now % 20) < 10) {
                    current = render_time();
                } else {
                    current = render_date();
                }
                break;
            }
            case DISPLAY_MODE_TIME:
            default:
                current = render_time();
                break;
        }

        // If NTP is stale, blink all digits and colons
        if (isNtpStale()) {
            if (subsec >= 500) {
                current = 0x787878787878ULL;
            }
            prev = current;
        } else {
            // Determine if date is currently shown
            bool showing_date = false;
            if (displayModeCurrent == DISPLAY_MODE_DATE) {
                showing_date = true;
            } else if (displayModeCurrent == DISPLAY_MODE_DATETIME) {
                time_t now = time(nullptr);
                if ((now % 20) >= 10) {
                    showing_date = true;
                }
            }

            // Use ternary to select colon mask
            uint64_t colon_mask = showing_date ? COLON_BOTTOM_BOTH : COLON_ALL;

            // Show colons if date is shown OR subsec < 500
            if (showing_date || subsec < 500) {
                current |= colon_mask;
                prev |= colon_mask;
            } else {
                current &= ~colon_mask;
                prev &= ~colon_mask;
            }
        }

        if (configDimmingDutyCycle < 32767 && (h >= configDimmingStart || h < configDimmingEnd)) {
            if (STATE_REFRESH_MODE != 1) {
                Serial.println("Switching to dimming mode");
                STATE_REFRESH_MODE = 1;
            }
            portENTER_CRITICAL(&displayMux);
            display_dimmed(current, configDimmingDutyCycle); // Use duty cycle as brightness
            portEXIT_CRITICAL(&displayMux);
        } else if (configBlendingDuration > 0) {
            if (STATE_REFRESH_MODE != 2) {
                Serial.println("Switching to blending mode");
                STATE_REFRESH_MODE = 2;
            }
            if (subsec == 0) {

                portENTER_CRITICAL(&displayMux);
                display_static(prev);
                portEXIT_CRITICAL(&displayMux);
            }
            else if (subsec <= configBlendingDuration) {
                if (current != prev) {
                    portENTER_CRITICAL(&displayMux);
                    display_blended(current, prev, (float)subsec / configBlendingDuration);
                    portEXIT_CRITICAL(&displayMux);

                }
            } else {
                portENTER_CRITICAL(&displayMux);
                display_static(current);
                portEXIT_CRITICAL(&displayMux);

                STATE_PREVIOUS = current;

            }
        } else if (current != prev) {
                portENTER_CRITICAL(&displayMux);
                display_static(current);
                portEXIT_CRITICAL(&displayMux);
        }
        displayTaskIterationsCount++;
        vTaskDelayUntil(&xLastWakeTime, interval);
    }
}


void setup() {
    Serial.println("Initalizing clock, data pins");
    pinMode(PIN_CLOCK, OUTPUT);
    pinMode(PIN_DATA, OUTPUT);
    if (!rmtInit(RMT_TX_GPIO, RMT_TX_MODE, RMT_MEM_NUM_BLOCKS_1, CONFIG_CPU_FREQUENCY / CONFIG_RMT_DIVISOR)) {
        Serial.println("RMT initialization failed\n");
    }
    display_static(0x787878787878ULL);

    Serial.begin(115200);
    setCpuFrequencyMhz(CONFIG_CPU_FREQUENCY / 1000000);

    // Setup WifiManager
    uint8_t mac[6];
    WiFi.macAddress(mac);
    char hostname[20];
    snprintf(hostname, sizeof(hostname), "Nixie%02X%02X%02X", mac[3], mac[4], mac[5]);
    wm.setHostname(hostname);
    wm.setTitle("Nixie");
    wm.setShowInfoUpdate(false); // https://github.com/tzapu/WiFiManager/issues/1262
    wm.setShowInfoErase(false);
    wm.setConfigPortalBlocking(false);
    wm.setMinimumSignalQuality(50);
    wm.setShowInfoUpdate(false);
    wm.addParameter(&paramNetworkTimeServer);
    wm.addParameter(&paramCity);
    wm.addParameter(&paramTimezone);
    wm.addParameter(&paramDisplayMode);
    wm.addParameter(&paramDisplayModeCombobox);
    wm.addParameter(&paramDimmingDutyCycle);
    wm.addParameter(&paramDimmingDutyCycleSlider);
    wm.addParameter(&paramDimmingStart);
    wm.addParameter(&paramDimmingStartCombobox);
    wm.addParameter(&paramDimmingEnd);
    wm.addParameter(&paramDimmingEndCombobox);
    wm.addParameter(&paramBlendingDuration);
    wm.addParameter(&paramBlendingDurationSlider);
    wm.addParameter(&paramHourFormat);
    wm.addParameter(&paramHourFormatCombobox);
    wm.setSaveParamsCallback(saveParamsCallback);
    wm.setConfigPortalTimeout(0);
    wm.startConfigPortal(hostname); // Set AP SSID to hostname
    wm.server->on("/metrics", handleMetrics);

    Serial.println("Autostarting wireless");
    if (!wm.autoConnect(hostname)) { // Set AP SSID to hostname
        Serial.println("Failed to connect or start config portal");
    } else {
        Serial.println("WiFi connected or config portal completed");
        WiFi.softAPdisconnect(true);
    }


    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS mount failed");
    } else {
        if (loadClockConfig() != 0) {
            Serial.println("Failed to load clock configuration from LittleFS, restoring defaults");
            saveParamsCallback();
            if (loadClockConfig() != 0) {
                Serial.println("Failed to reset LittleFS defaults");
            }
        } else {
            Serial.println("Configuration loaded");
        }
    }

    // Register SNTP time sync notification callback
    sntp_set_time_sync_notification_cb(timeavailable);

    // Start FreeRTOS display refresh task
    Serial.println("Starting display refresh task");
    xTaskCreatePinnedToCore(DisplayTask, "DisplayTask", 8192, NULL, 24, NULL, 0);
}

void loop() {
    wm.process();
    wifiManagerProcessCount++;
    vTaskDelay(pdMS_TO_TICKS(10)); // Keep loop responsive, but display is handled by DisplayTask
}
