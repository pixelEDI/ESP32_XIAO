
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
DEVBoard LED Test | V1.0 | 07.2024

*/

#include "button.h"
#include "leds.h"
#include <Arduino.h>

leds led1(D10);
leds led2(D9);
leds led3(D8);
leds led4(D7);

Button btn1(D2);
Button btn2(D3);

void checkButtons() {
  switch (btn1.checkBTN()) {
  case 1:
    led1.turnOn();
    led2.turnOn();
    break;
  case 2:
    led1.turnOff();
    led2.turnOff();
    break;
  }

  switch (btn2.checkBTN()) {
  case 1:
    led3.turnOn();
    led4.turnOn();
    break;
  case 2:
    led3.turnOff();
    led4.turnOff();
    break;
  }
}

void setup() {
  // Serial.begin(115200);
  //  pinmodes Buttons werden in der Klasse gesetzt
}

void loop() { checkButtons(); }
