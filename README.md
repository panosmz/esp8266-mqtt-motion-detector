ESP8266-based MQTT Motion Detector (PIR) :running:
==========================

A script to connect ESP8266-based PIR motion detectors to MQTT. Can be used with :house: [Home Assistant](https://github.com/home-assistant/home-assistant). Built using the [Arduino Core for ESP8266](https://github.com/esp8266/Arduino).

Requirements
------------
* [pubsubclient](https://github.com/knolleary/pubsubclient)

Setup Instructions
------------

* Clone this repository and copy the `src/sample.configuration.h` file to `src/configuration.h`:

    ````
    cp src/sample.configuration.h src/configuration.h
    ````
* Edit the `src/configuration.h` file to use your credentials.
* Install the required libraries.
* Build and upload to your ESP8266 using the [PlatformIO IDE](https://platformio.org/platformio-ide).