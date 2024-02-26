#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "globals.h"

#ifndef OLED_
#define OLED_

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void startOled()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
}

void showReady()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(32, 12);
  display.println("pixelPASS");
  display.setCursor(32, 21);
  display.println("Loading...");
  display.display();
}

void showTTOP()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(32, 13);
  display.println(myWebsites[chosenWebsite].name);
  display.setCursor(32, 21);
  display.println(myWebsites[chosenWebsite].onetimepw);
  // display.display(); wird später aufgerufen
}

void showTimeLine()
{
  int lineY = SCREEN_HEIGHT - 1;
  // hier wird gezaubert

  unsigned int timestampSeconds = myWebsites[chosenWebsite].unixtimestamp % 60;
  float procentFromSeconds = 0;

  if (timestampSeconds >= 30)
  {
    timestampSeconds = timestampSeconds - 30;
  }

  procentFromSeconds = timestampSeconds / 30.0 * 100.0;

  int x = 57; // x ist die länge von Linie am unteren Rand
  int decrementStep = (x * (procentFromSeconds / 100));
  int startPoint = 33;
  int endPoint = startPoint + decrementStep;

  display.drawLine(startPoint, lineY, endPoint, lineY, SSD1306_WHITE);
  display.display();
}

float mapf(float x, float inmin, float inmax, float outmin, float outmax)
{
  float a = x - inmin;
  float b = outmax - outmin;
  float c = inmax - inmin;
  return a * b / c + outmin;
}

void readBatteryVoltage()
{
  unsigned long millisBattery = 0;
  float Vbattf = 0;

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

  batteryleft = mapf(Vbattf, 3.3, 4.1, 0, 100);

  Serial.println(batteryleft, 3);
}

void isBLEConnected()
{
  if (bleKeyboard.isConnected())
  {
    display.drawBitmap(85, 13, bluetooth_connected_grafic, 16, 16, 1);
  }
}

#endif