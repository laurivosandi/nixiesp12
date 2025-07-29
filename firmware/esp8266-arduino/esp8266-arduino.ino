/*
https://github.com/laurivosandi/nixiesp12/blob/master/firmware/main.py
https://randomnerdtutorials.com/wifimanager-with-esp8266-autoconnect-custom-parameter-and-manage-your-ssid-and-password/
*/
#include <LittleFS.h>
#include <WiFiManager.h>
#include <ezTime.h>
#include "cities.h"

// #define DEBUG 1
// #define DIMMING_ENABLED 1
// #define TEST_SEQUENCE 1

#define PIN_CLOCK 3
#define PIN_DATA 2
#define PIN_LATCH 0

#define SUNRISE 6
#define SUNSET 22

// ezTime structs
tmElements_t tm;
Timezone local;

int configDimmingDutyCycle = 0;

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

#ifdef DIMMING_ENABLED
const char dimmerSliderSnippet[] = R"(
<br/><label for='dimming_duty_cycle_slider'>Night time dimming</label>
<input type="range" min="1" max="3840" value="1000" class="slider" id="dimming_duty_cycle_slider" onchange="document.getElementById('dimming_duty_cycle').value = this.value">
<script>
document.getElementById('dimming_duty_cycle').hidden = true;
</script>
)";
#endif

WiFiManagerParameter paramNetworkTimeServer("networkTimeServer", "Network time server", "ee.pool.ntp.org", 63);
WiFiManagerParameter paramDisplayMode("displayMode", "Will be hidden", "1", 2);
WiFiManagerParameter paramDisplayModeCombobox(displayModesCombobox);
WiFiManagerParameter paramCity(cities);
WiFiManagerParameter paramTimezone("timezone", "Timezone encoding", "EET-2EEST,M3.5.0/3,M10.5.0/4", 30);
//WiFiManagerParameter paramLong("long", "Longitude", "26", 10);
//WiFiManagerParameter paramLat("lat", "Latitude", "59", 10);

#ifdef DIMMING_ENABLED
WiFiManagerParameter paramDimmingDutyCycle("dimming_duty_cycle", "", "1000", 4);
WiFiManagerParameter paramDimmingDutyCycleSlider(dimmerSliderSnippet);

// Dimmer settings
volatile long displayInterruptCount = 0;
#endif

volatile bool blink = true;
int lookup[] = {11, 9, 12, 8, 0, 4, 1, 3, 2, 10};

void ICACHE_RAM_ATTR bitbang_bit(int value){
    if(value & 1){
        digitalWrite(PIN_DATA, HIGH);
    }
    else{
        digitalWrite(PIN_DATA, LOW);
    }
    digitalWrite(PIN_CLOCK, HIGH);
    digitalWrite(PIN_CLOCK, LOW);
}

void ICACHE_RAM_ATTR bitbang_digit(int digit){
    int i = 0;
    if (!blink && timeStatus() != timeSet) {
        for(i=0;i<4;i++){
            bitbang_bit(1);
        }
    } else {
        for(i=0;i<4;i++){
            bitbang_bit(lookup[digit] << i >> 3);
        }
    }
}

void ICACHE_RAM_ATTR renderTest(int j) {
    for(int i=0; i<6; i++){
        bitbang_bit(0);
        bitbang_digit(j);
        bitbang_bit(0);
        bitbang_bit(0);
        bitbang_bit(0);
    }
    digitalWrite(PIN_LATCH, HIGH);
    digitalWrite(PIN_LATCH, LOW);
}

void ICACHE_RAM_ATTR renderTime(){
    int hour = tm.Hour;
    int minute = tm.Minute;
    int second = tm.Second;
    bitbang_bit(0);
    bitbang_digit(hour / 10);
    bitbang_bit(0);
    bitbang_bit(0);
    bitbang_bit(0);

    bitbang_bit(0);
    bitbang_digit(hour % 10);
    bitbang_bit(blink);
    bitbang_bit(blink);
    bitbang_bit(blink);

    bitbang_bit(blink);
    bitbang_digit(minute / 10);
    bitbang_bit(0);
    bitbang_bit(0);
    bitbang_bit(0);

    bitbang_bit(0);
    bitbang_digit(minute % 10);
    bitbang_bit(blink);
    bitbang_bit(blink);
    bitbang_bit(blink);

    bitbang_bit(blink);
    bitbang_digit(second / 10);
    bitbang_bit(0);
    bitbang_bit(0);
    bitbang_bit(0);

    bitbang_bit(0);
    bitbang_digit(second % 10);
    bitbang_bit(0);
    bitbang_bit(0);
    bitbang_bit(0);
}

void ICACHE_RAM_ATTR renderDate(){
    int day = tm.Day;
    int month = tm.Month;
    int year = tm.Year-30;
    bitbang_bit(0);
    bitbang_digit((year) / 10);
    bitbang_bit(0);
    bitbang_bit(0);
    bitbang_bit(0);

    bitbang_bit(0);
    bitbang_digit((year) % 10);
    bitbang_bit(0);
    bitbang_bit(1);
    bitbang_bit(0);

    bitbang_bit(0);
    bitbang_digit(month/ 10);
    bitbang_bit(0);
    bitbang_bit(0);
    bitbang_bit(0);

    bitbang_bit(0);
    bitbang_digit(month % 10);
    bitbang_bit(0);
    bitbang_bit(1);
    bitbang_bit(0);

    bitbang_bit(0);
    bitbang_digit(day / 10);
    bitbang_bit(0);
    bitbang_bit(0);
    bitbang_bit(0);

    bitbang_bit(0);
    bitbang_digit(day % 10);
    bitbang_bit(0);
    bitbang_bit(0);
    bitbang_bit(0);
}

void ICACHE_RAM_ATTR renderDisplay() {
    switch (configDisplayModesEnabled) {
        case 1:
            renderTime();
            break;
        case 2:
            renderDate();
            break;
        case 3:
            if (millis() % 30000 < 15000) {
                renderTime();
            } else {
                renderDate();
            }
            break;
    }
    digitalWrite(PIN_LATCH, HIGH);
    digitalWrite(PIN_LATCH, LOW);
}

void ICACHE_RAM_ATTR clearDisplay() {
  for(int i=0; i<6; i++){
    bitbang_bit(1);
    bitbang_bit(0);
    bitbang_bit(0);
    bitbang_bit(0);
    bitbang_bit(0);
    bitbang_bit(1);
    bitbang_bit(1);
    bitbang_bit(1);
  }

  digitalWrite(PIN_LATCH, HIGH);
  digitalWrite(PIN_LATCH, LOW);
}

int counter = 0;

struct timeval tv;

#ifdef DIMMING_ENABLED
void ICACHE_RAM_ATTR dimmerTimerCallback() {
    noInterrupts();
    displayInterruptCount++;
    gettimeofday(&tv, NULL);
    blink = tv.tv_usec < 500000;
    int j = current_dimming_duty_cycle;
    if (j < configDimmingDutyCycle) {
        j = configDimmingDutyCycle;
    }

  //  if (counter == 0) {
        renderDisplay();
        timer1_write(j+1);
  //      counter = 1;
  //  } else if (counter == 1) {
  //      clearDisplay();
  //      timer1_write(3840-j+1);
  //      counter = 0;
  //  }
    interrupts();
}
#endif

int loadClockConfig() {

  unsigned char timezone[30] = {'\0'};
  File file = LittleFS.open("/timezone", "r");
  if (!file) { return 1; }
  if (!file.read(timezone, sizeof(timezone))) { return 2; }
  Serial.print("Using timezone: ");
  Serial.println((const char*)timezone);

  unsigned char timeserver[63] = {'\0'};
  file = LittleFS.open("/timeserver", "r");
  if (!file) { return 3; }
  if (!file.read(timeserver, sizeof(timeserver))) { return 4; }
  Serial.print("Using time server: ");
  Serial.println((const char*)timeserver);

  setServer((const char*)timeserver);
  local.setPosix((const char*)timezone);

  unsigned char modes[1] = {'\0'};
  file = LittleFS.open("/modes", "r");
  if (!file) { return 5; }
  if (!file.read(modes, sizeof(modes))) { return 6; }
  configDisplayModesEnabled = atoi((const char*)modes);
  Serial.print("Enabled display modes:");
  if (configDisplayModesEnabled & DISPLAY_MODE_DATE) {
    Serial.print(" DATE");
  }
  if (configDisplayModesEnabled & DISPLAY_MODE_TIME) {
    Serial.print(" TIME");
  }
  Serial.println();

  #ifdef DIMMING_ENABLED
  unsigned char bufDimming[10] = {'\0'};
  file = LittleFS.open("/dimming", "r");
  if (!file) { return 7; }
  if (!file.read(bufDimming, sizeof(bufDimming))) { return 8; }
  configDimmingDutyCycle = atoi((const char*)bufDimming);
  Serial.print("Night time dimming duty cycle: ");
  Serial.println((const char*)bufDimming);
  #endif

  return 0;
}

void saveParamsCallback() {
    File file = LittleFS.open("/timeserver", "w");
    file.print(paramNetworkTimeServer.getValue());
    file.close();

    file = LittleFS.open("/timezone", "w");
    file.print(paramTimezone.getValue());
    file.close();

    #ifdef DIMMING_ENABLED
    file = LittleFS.open("/dimming", "w");
    file.print(paramDimmingDutyCycle.getValue());
    file.close();
    #endif

    file = LittleFS.open("/modes", "w");
    file.print(paramDisplayMode.getValue());
    file.close();

    loadClockConfig();
}

void handleMetrics(){
    char tbuf[30];

    String buf = "";

    buf += "nixie_sketch_size_bytes ";
    buf += ESP.getSketchSize();
    buf += "\n";

    buf += "nixie_flash_space_bytes ";
    buf += ESP.getFlashChipRealSize();
    buf += "\n";

    buf += "nixie_free_heap_bytes ";
    buf += ESP.getFreeHeap();
    buf += "\n";

    #ifdef DIMMING_ENABLED
    buf += "nixie_display_interrupt_count ";
    buf += displayInterruptCount;
    buf += "\n";
    #endif

    buf += "nixie_ntp_last_sync_timestamp_seconds ";
    buf += lastNtpUpdateTime();
    buf += "\n";

    wm.server->send(200, "text/plain", buf);
}

void initializePins() {
    pinMode(PIN_CLOCK, OUTPUT);
    pinMode(PIN_LATCH, OUTPUT);
    pinMode(PIN_DATA, OUTPUT);
    digitalWrite(PIN_CLOCK, LOW);
    digitalWrite(PIN_LATCH, LOW);
    digitalWrite(PIN_DATA, LOW);
    clearDisplay();
}

void setup() {
    Serial.begin(9600);
    Serial.println("Nixie clock booting up");
    initializePins();

    #ifdef DEBUG
	  setDebug(INFO);
	  #endif

    #ifdef TEST_SEQUENCE
    for(int i = 0; i < 10; i++) {
      renderTest(i);
      delay(3000);
    }
    #endif

    wm.setDebugOutput(true);
    wm.setMinimumSignalQuality(50);

    if (!LittleFS.begin()) {
      Serial.println("LittleFS mount failed");
    } else {
      if(loadClockConfig() != 0) {
        Serial.println("Failed to load clock configuration from LittleFS");
      } else {
          Serial.println("Configuration loaded");
      }
    }
    wm.addParameter(&paramNetworkTimeServer);
    wm.addParameter(&paramCity);
    wm.addParameter(&paramTimezone);
    //wm.addParameter(&paramLong);
    //wm.addParameter(&paramLat);
    wm.addParameter(&paramDisplayMode);
    wm.addParameter(&paramDisplayModeCombobox);

    #ifdef DIMMING_ENABLED
    wm.addParameter(&paramDimmingDutyCycle);
    wm.addParameter(&paramDimmingDutyCycleSlider);
    #endif

    wm.setSaveParamsCallback(saveParamsCallback);
    wm.setShowInfoUpdate(false); // https://github.com/tzapu/WiFiManager/issues/1262
    wm.setShowInfoErase(false);
    wm.setConfigPortalBlocking(false);

    Serial.println("Autostarting wireless");

    wm.autoConnect();

    Serial.println("Starting config portal");


    wm.startConfigPortal();

    #ifdef DEBUG
    wm.server->on("/metrics", handleMetrics);
    #else
    wm.setDebugOutput(false);
    #endif

    renderNormal();
}


void renderNormal() {
    gettimeofday(&tv, NULL);
    blink = tv.tv_usec < 500000;
    breakTime(local.now(), tm);

    renderDisplay();
    delay((500 - (local.ms(LAST_READ) % 500)) + 1);

    #ifdef DEBUG
    Serial.print(1970+tm.Year);
    Serial.print("-");
    Serial.print(tm.Month);
    Serial.print("-");
    Serial.print(tm.Day);
    Serial.print(" ");
    Serial.print(tm.Hour);
    Serial.print(":");
    Serial.print(tm.Minute);
    Serial.print(":");
    Serial.print(tm.Second);
    Serial.print(".");
    Serial.println(local.ms(LAST_READ));
    #endif
}

void loop() {
    wm.process();
    events(); // this invokes yield()

    #ifdef DIMMING_ENABLED
    switch (operationModeCurrent) {
        case OPERATION_MODE_NORMAL:

            if ((tm.Hour < SUNRISE || tm.Hour > SUNSET) && timeStatus() == timeSet) {
                operationModeCurrent = OPERATION_MODE_DIMMED;
                #ifdef DEBUG
                Serial.println("Clock synchronized, disabling wireless, enabling dimming");
                #endif

                WiFi.disconnect();
                WiFi.mode(WIFI_OFF);

                timer1_attachInterrupt(dimmerTimerCallback);
                timer1_isr_init();
                timer1_enable(TIM_DIV256, TIM_EDGE, TIM_SINGLE);
                timer1_write(100);
            } else {
                renderNormal();
            }
            break;
        case OPERATION_MODE_DIMMED:
            if (tm.Hour > SUNRISE && tm.Hour < SUNSET) {
                operationModeCurrent = OPERATION_MODE_NORMAL;
                timer1_detachInterrupt();
                timer1_disable();

                #ifdef DEBUG
                Serial.println("Disabling dimming");
                #endif

                WiFi.mode(WIFI_STA);
            } else if (tm.Hour == SUNRISE) {
                current_dimming_duty_cycle = tm.Minute << 6;
            } else if (tm.Hour == SUNSET) {
                current_dimming_duty_cycle = (61 - tm.Minute) << 6;
            }
            break;
    }
    #else
    renderNormal();
    #endif
}
