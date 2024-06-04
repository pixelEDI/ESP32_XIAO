/*
        _          _ ______ _____ _____
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

www.pixeledi.eu |
PartDB Finder | V1.0 | 11/2023

*/

#include <Arduino.h>
#include "globals.h"
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include "credentials.h"
#include <PubSubClient.h>
#include "wifimqtt.h"


// variables in globals.h

void turnAllLedsOff()
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    strip.setPixelColor(i, 0, 0, 0); // Set pixel color to black (off)
  }
  strip.show();
}

void indicateCompartment()
{
  for (int i = neoleds.startled; i < neoleds.endled; i++)
      {
        strip.setBrightness(10);              
        strip.setPixelColor(i, strip.Color(neoleds.r, neoleds.g, neoleds.b)); // Farbe setzen (rot in diesem Fall)
      }
      strip.show();

}

void turnOffAfter(int turnoffMS)
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= turnoffMS)
  {
    previousMillis = currentMillis;
    turnAllLedsOff();
    state = WAIT;
  }
}

void setup()
{
  Serial.begin(115200);
  strip.begin();
  strip.show();
  strip.setBrightness(15);

  connectAP();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.setBufferSize(1024);

  previousMillis = millis();
}

void loop()
{

  if (!client.connected())
  {
    reconnect();
  }
  if (!client.loop())
  {
    client.connect("ESP32Shelf");
  }

  switch (state)
  {
  case STARTUP:
    //fancy stuff
    break;
  case INDICATE:
    indicateCompartment();
    turnOffAfter(3000);
    break;
  case CHANGED:
    turnAllLedsOff();
    state = INDICATE;
    break;
  case RAINBOW:

    break;
  case WAIT:
    previousMillis = millis();
    // just chillin
    break;
  }
}