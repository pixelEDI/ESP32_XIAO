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

void loadingDisplay()
{
    display.stopscroll();
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    String textToCenter = "Lade Daten...";
    int textWidth = textToCenter.length() * 6;
    int xPos = (SCREEN_WIDTH - textWidth) / 2;
    display.setCursor(0, 10);
    display.println(textToCenter);
    display.display();
}

void showValuesOnOled(byte elmnt)
{

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print(String(myFahrplan[elmnt].station));

    display.setCursor(0, 10);
    display.print(String(myFahrplan[elmnt].departure1));

    display.setCursor(0, 20);
    display.println(String(myFahrplan[elmnt].departure2));

    display.display();
    display.startscrollleft(0x00, 0x0F);
}

#endif