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
e-paper | V1.0 | 04.2024


*/
#include <Arduino.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include "credentials.h"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

#ifndef _TextDisplay_H_
#define _TextDisplay_H_

#include "GxEPD2_GFX.h"
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/TomThumb.h>

String type = "";
String setupJoke = "";
String punchline = "";
int id = 0;

// .pio -> libdeps -> seeed_xaio_esp32c3 -> GxEPD2 -> examples
// die notwendigen Codeteile stammen von dem HelloWorld Beispiel
// hier gibt es weitere Headerdatein für diverse andere Geräte, welche hier nicht eingebunden werden

GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=5*/ SS, /*DC=*/2, /*RST=*/3, /*BUSY=*/4)); // GDEH0154D67 200x200, SSD1681
String serverName = "https://official-joke-api.appspot.com/random_joke";

#endif

unsigned long previousMillis = millis();

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

    if (cnt > 20)
      ESP.restart();
  }
  Serial.println(WiFi.localIP());
}

void makeAPICall()
{
  Serial.println("getting Data...");
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    http.begin(serverName.c_str());
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0)
    {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload); 

    }
    else
    {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else
  {
    Serial.println("Reconnect to AP");
    connectAP();
  }
}



void setup()
{
  Serial.begin(115200);
  connectAP();

  display.init(115200);
  makeAPICall();
  display.hibernate();
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000 * 20 * 1)
  {
    previousMillis = currentMillis;

    makeAPICall();
    //Serial.println("E-Ink aktualisiert");
  }
}