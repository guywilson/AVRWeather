# AVRWeather

Split into the following sub-projects:

avr
---

Runs on an Arduino Uno (Atmega328p), written in C and built using the avr-gcc toolset. This uses the real-time scheduler from my RTScheduler repo.

wctl
----

Runs on a Raspberry Pi, written in C++ and talks to the avr software running on the Arduino via serial over USB. This will query the Arduino for waether data and post this to the web-app webserver.

web-app
-------

Runs on another Raspberry Pi, written in Nodejs and using a PostgreSQL database to store weather data (for drawing graphs)

weather-site
------------

The same as web-app, but written in Python with the Django framework
