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

// .pio -> libdeps -> seeed_xaio_esp32c3 -> GxEPD2 -> examples
// die notwendigen Codeteile stammen von dem HelloWorld Beispiel
// hier gibt es weitere Headerdatein für diverse andere Geräte, welche hier nicht eingebunden werden

GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=5*/ SS, /*DC=*/ 2, /*RST=*/ 3, /*BUSY=*/ 4)); // GDEH0154D67 200x200, SSD1681

#endif

unsigned long previousMillis = millis();

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
  showImage();
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