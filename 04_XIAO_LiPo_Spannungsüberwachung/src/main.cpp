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

unsigned long millisBattery = 0;
float Vbattf = 0;

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

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
    delay(1000);
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
    // voltage divider actual with 2x 100kOhm to A0
    // results in Voltage / 2
    // get rid of the spikes ->for loop with 16
    // calculate voltage
    Vbattf = 2 * Vbatt / 13 / 1000.0;

    Serial.println(Vbattf, 3);

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(35, 12);
    display.print("LiPo:");

    display.setCursor(35, 24);
    
    display.print(String(Vbattf,3));
    display.print(" V");

    display.display();
  }
}

void setup()
{
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  showReady();
}

void loop()
{
  readBatteryVoltage();
}