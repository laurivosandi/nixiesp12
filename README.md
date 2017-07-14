# NixiESP

Yet another Nixie clock project!

Some highlights:

* K155ID1 driven IN-12A or IN-12B tubes for hour, minute, seconds
* BS107 driven IN-6 or similar for separation
* ESP8266 for time synchronization and web interface
* LM1117 (3.3V regulator) for logic power supply
* No tube step up converter on-board, pin headers for connecting third party power supply 
* KiCad design with 3D models from http://miniwatt.info

Some KiCad screenshots:

<img src="nixiesp.png"/>


##Install

Boot ESP8266 with program pin held low and flash MicroPython:

```bash
esptool.py --port /dev/ttyUSB0 --baud 460800 erase_flash
esptool.py --port /dev/ttyUSB0 --baud 460800 write_flash --flash_size=detect 0 esp8266-20170612-v1.9.1.bin 
```

Upload main.py and boot.py and adjust network configuration in boot.py accordingly.
