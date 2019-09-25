#!/bin/bash

DEVICE=$1
TARGET=$2
#BAUDRATE=57600
BAUDRATE=115200

SERIALPORT="$(ls /dev/tty.* | grep usb)"

avrdude -Cavrdude.conf -v -p$DEVICE -carduino -P$SERIALPORT -b$BAUDRATE -D -Uflash:w:$TARGET:i
