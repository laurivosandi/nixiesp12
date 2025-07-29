SKETCH_FOLDER := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
#UPLOAD_PORT ?= /dev/ttyACM0
UPLOAD_PORT ?= /dev/ttyUSB0

all: $(SKETCH_FOLDER)/build/esp32c3-arduino.ino.bin

$(SKETCH_FOLDER)/cities.h: ../cities.py
	python3 ../cities.py > $(SKETCH_FOLDER)/cities.h

$(SKETCH_FOLDER)/build/esp32c3-arduino.ino.bin: $(SKETCH_FOLDER)/esp32c3-arduino.ino $(SKETCH_FOLDER)/cities.h
	arduino-cli compile -e -b esp32:esp32:esp32c3 $(SKETCH_FOLDER)

deps:
	arduino-cli config set network.connection_timeout 600s
	arduino-cli core install  esp32:esp32
	arduino-cli lib install wifimanager

erase:
	esptool.py --chip esp32c3 --port $(UPLOAD_PORT) erase_flash

flash-dev:
#	arduino-cli upload -b esp32:esp32:esp32c3:CDCOnBoot=cdc -p $(UPLOAD_PORT) $(SKETCH_FOLDER)
	arduino-cli compile --fqbn esp32:esp32:esp32c3:CDCOnBoot=cdc $(SKETCH_FOLDER) --upload -p /dev/ttyACM0
#	arduino-cli compile --fqbn esp32:esp32:esp32c3 $(SKETCH_FOLDER) --upload -p $(UPLOAD_PORT) --build-property build.extra_flags=-Os

flash:
	arduino-cli compile --fqbn esp32:esp32:esp32c3 $(SKETCH_FOLDER) --upload -p $(UPLOAD_PORT)


console-dev:
	picocom -b 115200 /dev/ttyACM0

console:
	picocom -b 115200 $(UPLOAD_PORT)
