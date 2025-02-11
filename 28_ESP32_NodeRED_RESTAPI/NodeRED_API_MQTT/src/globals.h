#include <Arduino.h>
#ifndef GLOBALS_
#define GLOBALS_

unsigned long previousMillis = millis();

enum { WAIT, SENDMQTT, REQUESTVIAMQTT } state;

struct sensordata {
  String room;
  String temperature;
  String humidity;
};

sensordata mySensorData;

#endif
