#!/bin/bash

DEVICE=$1
TARGET=$2
BAUDRATE=115200
SERIALPORT=/dev/ttyACM0

toggle -pin 12

if [ $? -ne 0 ]; then
    echo "Failed to toggle reset pin, did you forget to run with sudo?"
    exit $?
fi

avrdude -C avrdude.conf -v -p $DEVICE -c arduino -P $SERIALPORT -b $BAUDRATE -D -U flash:w:$TARGET:i
