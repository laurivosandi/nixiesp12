# NixiESP12

## Intro

Yet another Nixie clock project!

Some highlights:

* K155ID1 driven IN-12A or IN-12B tubes for hour, minute, seconds. Use 36k resistors on these tubes.
* BS108 driven IN-6 or [similar 4*10mm neon bulbs](https://www.aliexpress.com/item/32344955038.html?spm=a2g0s.9042311.0.0.6ab14c4dCxpPZ0) for digit separation. Use 270k resistors on these bulbs.
* 74HC595 for serial to parallel conversion
* ESP8266 for time synchronization. Use 1k resistors for pull-up.
* LM1117-3.3V and LM1117-5V regulators for logic power supply
* No tube step up converter on-board, pin headers for connecting
  <a href="http://www.ebay.com/itm/DC-5V-12V-to-170V-DC-High-Voltage-NIXIE-Power-Supply-Module-PSU-NIXIE-TUBE-ERA-/322511957768?hash=item4b1735ef08">third party power supply</a>
* KiCad design with 3D models from http://miniwatt.info

Some KiCad screenshots:

<img src="https://git.k-space.ee/lauri/nixiesp12/raw/master/nixiesp.png"/>


## Install

Install dependencies on an Ubuntu 18.04 box:

```bash
apt install -y python3-pip wget picocom make
pip3 install adafruit-ampy esptool
```

Boot ESP8266 with program pin held low and flash MicroPython:

```bash
cd firmware
make erase
make flash
```

Reboot ESP8266, open serial to to the controller and format filesystem:

```
import os
os.umount('/')
os.VfsLfs2.mkfs(bdev)
os.mount(bdev, '/')
```

Finish with by uploading scripts:

```bash
make upload
```

Power cycle the device and via WiFi connect to the device,
network name is MicroPython-XXXXXX and password is micropythoN.
Navigate to http://192.168.4.1 to start the configuration wizard.


## Configuring

If firmware is unable to connect to preconfigured wireless network
or it is started up for the first time wireless network
with password `micropythoN` is created.

Connect to that wireless network and open http://192.168.4.1
in web browser to configure the clock.


## Assembly tips

Some cheap 1117V regulators don't offer short circuit protection
and once blown pass through input voltage,
make sure you get ones with protection otherwise you can fry ESP8266
or serial-to-parallel chips.

Once the PCB is milled or etched make sure you clean the 180V rails thoroughly,
that voltage is high enough to cross gaps of 0.1mm.
Once that happens it burns a thick dark trace into the fiberglass of PCB and
it's pretty tricky to clean up.
The PCB is designed with 0.4mm clearance to be compliant with HV designs.
This clearance of course assumes that PCB traces are covered.
Either use solder mask or conformal coating.

Use the bench power supply to gradually power up the device,
at 9V set current limiter to 0.5A max.
5V linear regulator can be omitted and bypassed if 5V wall adapter is always used.
Otherwise 6V-12V wall adapters are suitable,
Thincan DBE60 9V wall adapters are pretty much perfect for the job.
Note that the higher the input voltage the more power is dissipated
as heat on the 3.3V and 5V voltage regulators, thus at 12V the device gets really hot.


## Debugging

* If you get nonsense reading during boot up sequence 0..9 likely the connection between serial-to-parallel chips and high voltage drivers
  is flaky. Either there are shorted pins or there is no connection at all. Check soldering joints and check for shorts between lines and line to ground.
* If single tube doesn't light up likely the gas has escaped the tube, find replacement tube.
* If single digit does not light up likely the tube socket pin is mangled or it is not properly soldered on the side where the PCB trace runs.
