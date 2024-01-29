/*
        _          _ ______ _____ _____
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

www.pixeledi.eu | https://links.pixeledi.eu
Haltestelle | V1.0 | 01.2024

  Daten werden in Node-RED aufbereitet
  Abgespecktes JSON via MQTT zu ESP32
  Achtung Größe vom übertragenen JSON muss in Struct (Globals) angepasst werden

*/

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "globals.h"
#include "oled.h"
#include "wifimqtt.h"

void setup()
{
  Serial.begin(115200);
  startOled();
  loadingDisplay();

  connectAP();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.setBufferSize(1024);

  previousMillis = millis();
  state = GETNEWDATA;
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  if (!client.loop())
    client.connect("ESP32-DATA");

  unsigned long currentMillis = millis();

  switch (state)
  {
  case GETNEWDATA:
    if (currentMillis - previousMillis >= 2000)
    {
      client.publish("bushaltestelle/anfrage", "get new Data");
      state=WAIT;
    }

    break;
  case WAIT:
    if (currentMillis - previousMillis >= (1000 * 15))
    {
       previousMillis = millis();
       state=GETNEWDATA;
    }
    break;
  case SHOWDATA:
      Serial.print("Haltestelle: ");
    Serial.println(myFahrplan[0].station);
    Serial.print("departure1: ");
    Serial.println(myFahrplan[0].departure1);
    Serial.print("departure1: ");
    Serial.println(myFahrplan[0].departure2);
    Serial.print("departure1: ");
    Serial.println(myFahrplan[0].departure3);
    Serial.println();

    showValuesOnOled(0);

    state=WAIT;

   break;
  }
}
