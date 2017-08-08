# NixiESP12

## Intro

Yet another Nixie clock project!

Some highlights:

* K155ID1 driven IN-12A or IN-12B tubes for hour, minute, seconds
* BS107 driven IN-6 or similar for digit separation
* 74HC595 for serial to parallel conversion
* ESP8266 for time synchronization
* LM1117-3.3V and LM1117-5V regulators for logic power supply
* No tube step up converter on-board, pin headers for connecting
  <a href="http://www.ebay.com/itm/DC-5V-12V-to-170V-DC-High-Voltage-NIXIE-Power-Supply-Module-PSU-NIXIE-TUBE-ERA-/322511957768?hash=item4b1735ef08">third party power supply</a>
* KiCad design with 3D models from http://miniwatt.info

Some KiCad screenshots:

<img src="nixiesp.png"/>

Photos:

<img src="photo.jpg"/>


## Install

Boot ESP8266 with program pin held low and flash MicroPython:

```bash
esptool.py --port /dev/ttyUSB0 --baud 460800 erase_flash
esptool.py --port /dev/ttyUSB0 --baud 460800 write_flash --flash_size=detect 0 esp8266-20170612-v1.9.1.bin 
```

Upload main.py and boot.py and adjust network configuration in boot.py accordingly.

## Assembly tips

Some cheap 1117V regulators don't offer short circuit protection
and once blown pass through input voltage,
make sure you get ones with protection otherwise you can fry ESP8266
or serial-to-parallel chips.

Once the PCB is milled or etched make sure you clean the 180V rails thoroughly,
that voltage is high enough to cross gaps of 0.1mm.
Once that happens it burns a thick dark trace into the fiberglass of PCB and
it's pretty tricky to clean up.
