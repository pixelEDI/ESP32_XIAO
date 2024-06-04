#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#ifndef GLOBALS_
#define GLOBALS_

enum states {
  STARTUP,
  INDICATE,
  CHANGED,
  RAINBOW,
  WAIT
} state;

struct neoled{
  int startled;
  int endled;
  String shelf;
  byte r;
  byte g;
  byte b;
} neoleds;

#define PIN D6
#define NUM_LEDS 12
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long lastUpdate = 0; 
unsigned long previousMillis = millis();

int hue = 0;  // Startfarbe
int rainbowcycleDelay=20;

#endif