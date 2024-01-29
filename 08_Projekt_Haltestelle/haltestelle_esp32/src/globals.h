#include <Arduino.h>
#ifndef GLOBALS_
#define GLOBALS_

unsigned long previousMillis = millis();

enum states {
  GETNEWDATA,
  SHOWDATA,
  WAIT
} state;

struct fahrplan{
  String station;
  String departure1;
  String departure2;
  String departure3;
};

fahrplan myFahrplan[1];

#endif