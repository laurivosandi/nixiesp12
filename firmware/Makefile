NAME=esp8266-20180511-v1.9.4.bin

flash:
	wget -c http://micropython.org/resources/firmware/${NAME}
	esptool.py -p /dev/ttyUSB0 write_flash 0 ${NAME}

erase:
	esptool.py -p /dev/ttyUSB0 erase_flash

upload:
	ampy -p /dev/ttyUSB0 put picoweb.py
	ampy -p /dev/ttyUSB0 put timezone.py
	ampy -p /dev/ttyUSB0 put main.py

console:
	echo "Ctrl-A + Ctrl-Q to close Picocom"
	picocom -b115200 /dev/ttyUSB0
