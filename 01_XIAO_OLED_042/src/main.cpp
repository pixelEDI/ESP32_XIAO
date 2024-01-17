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
ESP32 XIAO mit OLED 0,42 | V1.0 | 01.2024
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

unsigned long previousMillis = millis();
int sec = 0;

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(2);
  display.setTextColor(WHITE);
}
void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= (1000 * 1))
  {
    previousMillis = currentMillis;
    display.clearDisplay();
    display.setCursor(36, 12);
    sec++;
    display.println(String(sec, DEC));
    display.display();
  }
}