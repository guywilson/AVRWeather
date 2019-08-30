# AVRWeather

The Arduino AVR code for the weather station. Runs on an Arduino Uno (Atmega328p), written in C and built using the avr-gcc toolset. This uses the real-time scheduler from my RTScheduler repo. I split these out to make it easier for people to use RTScheduler for their own projects.

The code responds to the following commands sent over the serial port (from weatherctl running on a Raspberry Pi):
