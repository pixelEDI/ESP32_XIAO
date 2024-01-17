/*
        _          _ ______ _____ _____
       (_)        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

www.pixeledi.eu | https://linktr.ee/pixeledi
ESP32 XIAO Battery Voltage | V1.0 | 04.2023

https://forum.seeedstudio.com/t/battery-voltage-monitor-and-ad-conversion-for-xiao-esp32c/267535

*/

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "batterygrafic.h"

unsigned long millisBattery = 0;
float Vbattf = 0;

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

float mapf(float x, float inmin, float inmax, float outmin, float outmax)
{
  float a = x - inmin;
  float b = outmax - outmin;
  float c = inmax - inmin;
  return a * b / c + outmin;
}

void setBitamp(const uint8_t bitmap_grafic[])
{
  display.drawBitmap(45, 20, bitmap_grafic, 20, 11, 1);
}

void showBatteryStatus()
{
  display.clearDisplay();

  // convert upper and lower LiPo Voltage threadshold in Percentage
  float batteryleft = mapf(Vbattf, 3.3, 4.2, 0, 100);

  if (batteryleft >= 50.0)
    setBitamp(bitmap_batteryfull);
  else if (batteryleft > 10.0 && batteryleft < 49.9)
    setBitamp(bitmap_batteryhaveFull);
  else if (batteryleft <= 9.9)
    setBitamp(bitmap_Battery_Status_10perc);
  else
    setBitamp(bitmap_batteryfull);

  display.setTextSize(1);
  display.setCursor(50, 12);
  display.print(String(Vbattf,2)+"V");
  display.setCursor(70,23);
  display.print(String(round(batteryleft),0)+"%");

  display.display();
}

void showReady()
{
  for (int i = 0; i < 4; i++)
  {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(35, 15);
    if (i == 0)
      display.print("READY");
    else if (i == 1)
      display.print("--3--");
    else if (i == 2)
      display.print("--2--");
    else if (i == 3)
      display.print("--1--");

    display.display();
    delay(300);
  }
}

void readBatteryVoltage()
{
  if (millis() - millisBattery > (300 * 1))
  {
    millisBattery = millis();

    uint32_t Vbatt = 0;
    for (int i = 0; i < 13; i++)
    {
      Vbatt = Vbatt + analogReadMilliVolts(A0);
    }
    // Spannungsteiler mit 2x 100kOhm zu A0
    // Die gemessene Spannung ist somit die Hälfte der Batteriespannung
    // weshalb später die Batteriespannung mit 2 multipliziert wird
    // Glätten von Spannungspsitzen -> Forloop 
    
    // = 2* -> Spannungsteiler
    // /13 -> Glättung
    // / 1000 -> mv in V
    Vbattf = 2 * Vbatt / 13 / 1000.0;

    Serial.println(Vbattf, 3);
  }
}

void setup()
{
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  showReady();
}

void loop()
{
  readBatteryVoltage();
  //debug zum testen der Grafiken
  //Vbattf=3.6;
  // debug ende

  showBatteryStatus();
}