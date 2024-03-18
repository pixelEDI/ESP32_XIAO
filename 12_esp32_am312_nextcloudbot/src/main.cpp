/*
        _          _ ______ _____ _____
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

https://links.pixeledi.eu
ESP32 & AM312 | V1.0 | 03.2024

*/

#include <Arduino.h>
#include <WiFi.h>
#include "credentials.h"
#include <PubSubClient.h>
#include "wifimqtt.h"
#include <ArduinoJson.h>

const byte pirPin = D6;
const byte led = D8;

void setup()
{
  Serial.begin(115200);

  pinMode(pirPin, INPUT);
  pinMode(led, OUTPUT);

  connectAP();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  // mqtt packet size
  client.setBufferSize(1024);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  if (!client.loop())
  {
    client.connect("ESP32-PIR");
  }

  // unsigned long currentMillis = millis();

  // Lese den Status des Bewegungssensors
  int pirState = digitalRead(pirPin);

  // Wenn Bewegung erkannt wird, gib eine Nachricht aus
  if (pirState == HIGH)
  {
    Serial.println("Bewegung erkannt!");
    digitalWrite(led, HIGH);
    client.publish("garten/pir1", "Bewegung erkannt");
    delay(5000);
  }
  else
  {
    Serial.println("Keine Bewegung.");
    digitalWrite(led, LOW);
  }

  delay(10);

}
