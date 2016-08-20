# Hardpass Prototype, v.2
A Raspberry Pi Zero based WiFi Enabled Hardware Password Manager, now with a PCB.

## Currently Implemented:
 - OLED (demo)
 - USB Gadgets (full)
 - USB HID send keys progam

## TODO
- OLED: Menu program
- WiFi: compile & install driver
- Button Matrix (same program as OLED)

## Install ESP driver
If you want to use the ESP8266 on the SDIO pins of the Pi, download and install the driver from Andrew Litt.
```sh
# on the pi:
git clone https://github.com/al177/esp8089.git
make && sudo make install
```

## In this repository
This repository contains:
 * USB HID progam `scan` with examples in `./send_hid`
 * OLED menu system in `./oled`, using the `ArduiPi_OLED` driver from http://hallard.me
 * Patcher and installer for `pass` in `./pass`
 * KiCAD schematic and PCB layout in `./kicad`


## Setting up
To automatically load necessary kernel modules for the OLED on boot, run as root on the Pi:
```sh
echo "i2c-dev">>/etc/modules
echo "dwc2">>/etc/modules
```

A small systemd unit file is included; place it in `/etc/systemd/system/` and modify it, so it points to `init_usb.sh`, which you can also modify to your needs. 

## License
I hereby release my work under the GNU GPLv3 where applicable. The complete license text, if not included, can be read at `https://www.gnu.org/licenses/gpl-3.0.txt`. Where the GPLv3 isn't applicable, the work is released under the Creative Commons Attribution-ShareAlike 4.0 International. 
This repository also includes the ArduiPi_OLED library from [hallard](https://github.com/hallard); see [this website](http://hallard.me/adafruit-oled-display-driver-for-pi/) for details.
and the kicad-ESP8266 library from [jdunmire](https://github.com/jdunmire/kicad-ESP8266), which is released under the Creative Commons Attribution-ShareAlike 4.0 International License. 
