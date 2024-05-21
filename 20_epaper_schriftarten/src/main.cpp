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
1.54" E-Paper | V1.0 | 05.2024

*/
#include <Arduino.h>
#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/TomThumb.h>
#include <Fonts/Tiny3x3a2pt7b.h>
#include <Fonts/Picopixel.h>
#include <Fonts/Org_01.h>
#include <Fonts/FreeSerifItalic12pt7b.h>


#define MAX_DISPLAY_BUFFER_SIZE 800
GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=*/5, /*DC=*/2, /*RST=*/3, /*BUSY=*/4)); // GDEH0154D67 200x200, SSD1681

unsigned long previousMillis = 0;
const char HelloWorld[] = "Hello pixelEDI";
void showFonts()
{
  display.setRotation(0);
  display.setFullWindow();

  do
  {
    display.fillScreen(GxEPD_WHITE);

    // Beispiel für die Verwendung von verschiedenen Schriftarten
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(10, 10);
    display.print("FreeMonoBold9pt7b");

    display.setFont(&FreeMono9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(10, 30);
    display.print("FreeMono9pt7b");

    display.setFont(&FreeSans9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(10, 50);
    display.print("FreeSans9pt7b");

    display.setFont(&FreeSerif9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(10, 70);
    display.print("FreeSerif9pt7b");

    display.setFont(&TomThumb);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(10, 90);
    display.print("TomThumb");

    display.setFont(&Tiny3x3a2pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(10, 110);
    display.print("Tiny3x3a2pt7b");

    display.setFont(&Picopixel);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(10, 130);
    display.print("Picopixel");

    display.setFont(&Org_01);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(10, 140);
    display.print("Org_01");

    display.setFont(&FreeSerifItalic12pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(10, 160);
    display.print("FreeSerifItalic12pt7b");

    

  } while (display.nextPage());
}

void setup()
{
  // display.init(115200); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  // helloWorld();
  delay(500);
  showFonts();
  display.hibernate();
}

void loop()
{
}
