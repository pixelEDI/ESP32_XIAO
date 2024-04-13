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
#include <WiFi.h>
#include <PubSubClient.h>
#include "wifimqtt.h"
#include "images.h"


#ifndef _TextDisplay_H_
#define _TextDisplay_H_

#include "GxEPD2_GFX.h"
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/TomThumb.h>

// .pio -> libdeps -> seeed_xaio_esp32c3 -> GxEPD2 -> examples
// die notwendigen Codeteile stammen von dem HelloWorld Beispiel
// hier gibt es weitere Headerdatein für diverse andere Geräte, welche hier nicht eingebunden werden

GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=5*/ SS, /*DC=*/ 2, /*RST=*/ 3, /*BUSY=*/ 4)); // GDEH0154D67 200x200, SSD1681

#endif

unsigned long previousMillis = millis();

void showText()
{
  display.setRotation(2);
  display.setTextColor(GxEPD_BLACK);

  display.firstPage();
  do
  {
    display.drawInvertedBitmap(0, 0, background_image, 200, 200, GxEPD_BLACK);

    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(75, 13);
    display.print("Edi");
    display.setCursor(35, 117);
    display.print("Mrs. Columbo");

    // top
    display.setFont(&TomThumb);
    display.setCursor(15, 40);
    display.print("11x");

    display.setFont(&FreeMono9pt7b);
    display.setCursor(75, 40);
    display.print("05h 05m");
    display.setCursor(75, 63);
    display.print("125 km");
    display.setCursor(75, 83);
    display.print("123 S/min");

    // bottom
    display.setFont(&TomThumb);
    display.setCursor(10, 137);
    display.print("23x");

    display.setFont(&FreeMono9pt7b);
    display.setCursor(75, 140);
    display.print("01h 05m");
    display.setCursor(75, 163);
    display.print("105 km");
    display.setCursor(75, 183);
    display.print("95 S/min");

    // Datum der Zusammenfassung
    display.setFont(&TomThumb);
    display.setCursor(160, 5);
    display.print("04.2024");

    //updated
    display.setFont(&TomThumb);
    display.setCursor(110, 197);
    display.print("updated: 12.04.24 08:10");

  } while (display.nextPage());
}


void showImage(){
  display.setRotation(2);
  display.setFullWindow();

  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.drawInvertedBitmap(0,0, background_image, 200, 200, GxEPD_BLACK);
  }
  while (display.nextPage());
}

void helloWorld_minimum(){
  display.init();
  display.setTextColor(GxEPD_BLACK);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.print("Hello ESP32 XIAO");
  }
  while (display.nextPage());
}


void setup()
{
  Serial.begin(115200);

  display.init(115200);
  delay(1000);

  showText();
  // helloWorld_minimum();
  
  // connectAP();
  // client.setServer(mqtt_server, 1883);
  // client.setCallback(callback);

  // previousMillis = millis();
}

void loop()
{
  // if (!client.connected())
  // {
  //   reconnect();
  // }
  // if (!client.loop())
  //   client.connect("esp_epaper");

  // unsigned long currentMillis = millis();

  // if (currentMillis - previousMillis >= 2000)
  // {
  //   previousMillis = currentMillis;
  //   
  // }
}