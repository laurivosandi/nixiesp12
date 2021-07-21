NAME=esp8266-1m-20210618-v1.16.bin

flash:
	wget -c http://micropython.org/resources/firmware/${NAME}
	esptool.py -p /dev/ttyUSB0 write_flash --flash_size=1MB 0 ${NAME}

erase:
	esptool.py -p /dev/ttyUSB0 erase_flash

upload:
	ampy -p /dev/ttyUSB0 put picoweb.py
	ampy -p /dev/ttyUSB0 put timezone.py
	ampy -p /dev/ttyUSB0 put main.py

console:
	echo "Ctrl-A + Ctrl-Q to close Picocom"
	picocom -b115200 /dev/ttyUSB0

clone_read:
	esptool.py -p /dev/ttyUSB0  read_flash 0 0x100000 clone.bin

clone_write:
	esptool.py -p /dev/ttyUSB0 write_flash --flash_size=1MB 0 clone.bin
