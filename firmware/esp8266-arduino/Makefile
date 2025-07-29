SKETCH_FOLDER := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
UPLOAD_PORT ?= /dev/ttyUSB0

all: $(SKETCH_FOLDER)/build/esp8266-arduino.ino.bin

$(SKETCH_FOLDER)/cities.h: ../cities.py
	python3 ../cities.py > $(SKETCH_FOLDER)/cities.h

$(SKETCH_FOLDER)/build/esp8266-arduino.ino.bin: $(SKETCH_FOLDER)/esp8266-arduino.ino $(SKETCH_FOLDER)/cities.h
	arduino-cli compile -e -b esp8266:esp8266:generic $(SKETCH_FOLDER)

deps:
	arduino-cli config set network.connection_timeout 600s
	arduino-cli core install \
	--additional-urls=http://arduino.esp8266.com/stable/package_esp8266com_index.json esp8266:esp8266
	arduino-cli lib install wifimanager ESP8266TimerInterrupt ezTime

flash: $(SKETCH_FOLDER)/esp8266-arduino.ino.bin
	arduino-cli upload -b esp8266:esp8266:generic -p $(UPLOAD_PORT) $(SKETCH_FOLDER)

console:
	picocom -b 9600 $(UPLOAD_PORT)
