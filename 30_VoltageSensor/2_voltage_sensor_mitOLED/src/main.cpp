
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
Voltage Sensor | V1.0 | 02.2025


*/

#include "button.h"
#include "leds.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
const int voltageSensorPin = A2;

leds led1(10);

float vin = 0.0;
float vmeasure = 0.0;
int voltageSensorVal = 0;
float vcc = 3.3;
const float spannungsteilerfactor = 5;

unsigned long previousMillis = 0;

bool showVoltage = false;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Button btn1(D3);

void calcVIN() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    vin = 0;
    for (int i = 0; i < 16; i++) {
      vin = vin + analogReadMilliVolts(voltageSensorPin);
    }
    vmeasure = spannungsteilerfactor * vin / 16 / 1000.0;
  }
}

void showWarning() {
  if (vmeasure <= 11.0) {
    led1.pulsate(20);
  }
}

void checkButtons() {
  switch (btn1.checkBTN()) {
  case 1:
    showVoltage = true;
    break;
  case 2:
    showVoltage = false;
    break;
  }
}

void initOled() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Hello XIAO!"));
  display.display();
  delay(500);
}

void setup() {
  Serial.begin(115200);
  initOled();
}

void loop() {

  checkButtons();

  calcVIN();

  showWarning();

  if (showVoltage) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Spannung in V");

    display.setCursor(0, 20);
    display.println(vmeasure);

    display.display();
  } else {
    display.clearDisplay();
    display.display();
  }
}
