#include <Arduino.h>
#include <WiFi.h>
#include "credentials.h"


time_t printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
  }

  time_t unixTime = mktime(&timeinfo);
  Serial.println(unixTime);
  Serial.println(&timeinfo);

  return unixTime;
}



void connectAP()
{
  Serial.println("Connecting to WiFi..");
  WiFi.begin(ssid, password);

  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
    cnt++;

    if (cnt > 30)
      ESP.restart();
  }
  Serial.println(WiFi.localIP());
}