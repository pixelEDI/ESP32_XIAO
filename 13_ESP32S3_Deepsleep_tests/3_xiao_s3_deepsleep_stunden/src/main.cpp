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
ESP32 XIAO S3 DeepSleep | V1.0 | 03.2024

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html
*/
#include <Arduino.h>
#include "wifimqtt.h"

unsigned long previousMillis = millis();
int cnt = 0;

uint64_t sleeptime = 60 * 60 * 1e6;
uint64_t sleeptime_debug = 10 * 1e6;
RTC_DATA_ATTR int bootCount = 0;
int wieLangeSchlafenInStunden = 10;

void setDeepSleep()
{
  Serial.println("Going to sleep zzZZZzz");
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  ESP.deepSleep(sleeptime_debug);
}

void setup()
{
  Serial.begin(115200);
  //delay(1000);


  ++bootCount;
 
  if (bootCount < wieLangeSchlafenInStunden)
  {
    setDeepSleep();
  }
  else
  {
    bootCount = 0; // Reset bootCount after waking up from sleep
  }
 

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
    client.connect("ESP32DeepsleepTest");
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= (1000 * 1))
  {
    previousMillis = currentMillis;
    cnt++;
    Serial.println(cnt);
  }

  if (cnt > 5)
  {
    cnt = 0;
    client.publish("deepsleeptest", "i am so tired");
    delay(300);
    setDeepSleep();
  }
}