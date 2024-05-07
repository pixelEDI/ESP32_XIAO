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
3 color 2.9" E-Paper | V1.0 | 04.2024

*/
#include <Arduino.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include "eink_image.h"
#include "credentials.h"
#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define MAX_DISPLAY_BUFFER_SIZE 800

#define MAX_HEIGHT_3C(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))
GxEPD2_3C<GxEPD2_290c, MAX_HEIGHT_3C(GxEPD2_290c)> display(GxEPD2_290c(/*CS=*/5, /*DC=*/2, /*RST=*/3, /*BUSY=*/4)); // GDEW029Z10 128x296, UC8151 (IL0373

unsigned long previousMillis = 0;
String serverName = "https://catfact.ninja/fact?max_length=75";

// wird für die Darstellung mit Zeilenumbruch verwendet
String row1, row2, row3, row4, row5, row6;
String catFacts = "";
String row[] = {
    row1,
    row2,
    row3,
    row4,
    row5,
    row6,
};

String nextWord(String x)
{
  return x.substring(0, x.indexOf(' '));
}

void formatString()
{

  for (int i = 0; i < 6; i++)
  {
    row[i] = "";
  }

  // Text soll in 6 Zeilen
  // Jede Zeile soll nicht länger als x Zeichen lang sein
  // Nur ganze Wörter kürzen
  int zeilenlaenge = 15;
  for (int i = 0; i < 6; i++)
  {
    while (row[i].length() + nextWord(catFacts).length() < zeilenlaenge)
    {
      row[i] = row[i] + " " + nextWord(catFacts);
      catFacts = catFacts.substring(nextWord(catFacts).length() + 1, catFacts.length());
    }
  }
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

    if (cnt > 20)
      ESP.restart();
  }
  Serial.println(WiFi.localIP());
}

void getcatFacts()
{
  Serial.println("Getting Cat-Facts...");
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
      // Serial.println(payload);

      // JSON Output from https://arduinojson.org/v6/assistant

      StaticJsonDocument<128> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (error)
      {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.c_str());
        return;
      }

      const char *fact = doc["fact"];
      int length = doc["length"];

      catFacts = String(fact);

      Serial.println(String(fact));
      Serial.println(String(length));
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

void showImage()
{
  display.setRotation(1);
  display.setFullWindow();

  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.drawInvertedBitmap(0, 0, cat, 296, 128, GxEPD_BLACK);
    display.drawInvertedBitmap(0, 0, cat_eyes, 296, 128, GxEPD_RED);
  } while (display.nextPage());
}

void showText()
{
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_RED);
  int box_x = 10;
  int box_y = 22;
  int box_w = 180;
  int box_h = 85;
  display.setPartialWindow(box_x, box_y, box_w, box_h);
  display.firstPage();
  do
  {
    display.fillRect(box_x, box_y, box_w, box_h, GxEPD_WHITE);

    // Alle Zeilen ausgeben
    for (int i = 0; i < 6; i++)
    {
      display.setCursor(10, (i * 15) + 32);
      display.print(row[i]);
    }
  } while (display.nextPage());
}

void refreshCatFacts()
{
  getcatFacts();
  formatString();
  showText();
}

void setup()
{
  Serial.begin(115200);
  connectAP();

  display.init(115200);
  showImage();
  delay(1000);
  refreshCatFacts();
  display.hibernate();
}

void loop()
{

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000 * 60 * 1)
  {
    previousMillis = currentMillis;

    refreshCatFacts();
    Serial.println("E-Ink aktualisiert");
  }
}
