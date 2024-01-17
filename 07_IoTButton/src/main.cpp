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
IoT Button | V1.0 | 01.2024

*/

#include <Arduino.h>
#include <ArduinoJson.h>
#include "wifimqtt.h"

unsigned long previousMillis = millis();

void setup()
{
  Serial.begin(115200);

  connectAP();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  if (!client.loop())
    client.connect("ESP32IoTButton");

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= (1000 * 20))
  {
    previousMillis = currentMillis;
    client.publish("office/iotbutton", "23");
    delay(1000);
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
    esp_deep_sleep_start();
    Serial.println("Going to Sleep zzZZZzzZZZ");
  }
}
