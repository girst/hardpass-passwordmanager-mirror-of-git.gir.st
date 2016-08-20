#!/bin/bash
 
# monitor GPIO pin 17 for shutdown signal
 
# export GPIO pin 17 and set to input with pull-up
echo "17" > /sys/class/gpio/export
echo "in" > /sys/class/gpio/gpio17/direction
echo "high" > /sys/class/gpio/gpio17/direction
 
# wait for pin to go low
while [ true ]
do
if [ "$(cat /sys/class/gpio/gpio17/value)" == '0' ]
then
 echo "Raspberry Pi Shutting Down!"
 #halt &
 shutdown -h now
 exit 0
fi
sleep 1
done
