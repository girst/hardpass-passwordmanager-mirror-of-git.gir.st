#!/bin/bash
# this file is from: https://github.com/ckuethe/usbarmory/wiki/USB-Gadgets
echo "creating composite mass-storage, serial, ethernet, hid..."
modprobe libcomposite

# assumes a disk image exists here...
FILE=/home/pi/hardpass/usbdisk.img
mkdir -p ${FILE/img/d}
mount -o loop,ro,offset=2048 -t vfat $FILE ${FILE/img/d}
cd /sys/kernel/config/usb_gadget/

mkdir -p g1
cd g1
#echo '' > UDC

echo 0x1d6b > idVendor # Linux Foundation
echo 0x0104 > idProduct # Multifunction Composite Gadget
echo 0x0100 > bcdDevice # v1.0.0
echo 0x0200 > bcdUSB # USB2

mkdir -p strings/0x409
echo "fedcba9876543210" > strings/0x409/serialnumber
echo "girst" > strings/0x409/manufacturer 
echo "Hardpass" > strings/0x409/product 

N="usb0"
mkdir -p functions/acm.$N
mkdir -p functions/ecm.$N
mkdir -p functions/hid.$N
mkdir -p functions/mass_storage.$N

# first byte of address must be even
HOST="48:6f:73:74:50:43" # "HostPC"
SELF="42:61:64:55:53:42" # "BadUSB"
echo $HOST > functions/ecm.$N/host_addr
echo $SELF > functions/ecm.$N/dev_addr

echo 1 > functions/mass_storage.$N/stall
echo 0 > functions/mass_storage.$N/lun.0/cdrom
echo 0 > functions/mass_storage.$N/lun.0/ro
echo 0 > functions/mass_storage.$N/lun.0/nofua
echo $FILE > functions/mass_storage.$N/lun.0/file

echo 1 > functions/hid.usb0/protocol
echo 1 > functions/hid.usb0/subclass
echo 8 > functions/hid.usb0/report_length
echo -ne \\x05\\x01\\x09\\x06\\xa1\\x01\\x05\\x07\\x19\\xe0\\x29\\xe7\\x15\\x00\\x25\\x01\\x75\\x01\\x95\\x08\\x81\\x02\\x95\\x01\\x75\\x08\\x81\\x03\\x95\\x05\\x75\\x01\\x05\\x08\\x19\\x01\\x29\\x05\\x91\\x02\\x95\\x01\\x75\\x03\\x91\\x03\\x95\\x06\\x75\\x08\\x15\\x00\\x25\\x65\\x05\\x07\\x19\\x00\\x29\\x65\\x81\\x00\\xc0 > functions/hid.usb0/report_desc


C=1
mkdir -p configs/c.$C/strings/0x409
echo "Config $C: ECM network" > configs/c.$C/strings/0x409/configuration 
echo 250 > configs/c.$C/MaxPower 
ln -s functions/acm.$N configs/c.$C/
ln -s functions/ecm.$N configs/c.$C/
ln -s functions/mass_storage.$N configs/c.$C/
ln -s functions/hid.$N configs/c.$C/

# this lists available UDC drivers
ls /sys/class/udc > UDC

ifconfig $N 10.0.0.1 netmask 255.255.255.252 up
route add -net default gw 10.0.0.2
echo "done. "
#echo "initializing demo menu..."
#while 1; do
#	/home/pi/hardpass/oled/run.sh
#done &
echo "starting shutdown 'daemon'"
/home/pi/hardpass/shutdown/shutdown-button.sh &
