/*
        _          _ ______ _____ _____
       |_|        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

https://links.pixeledi.eu
Ticker mit Button | V1.0 | 05.2024
*/

#include <Arduino.h>
#include <Ticker.h>

const byte LED_PIN = 10;
const byte BUTTON_PIN = 8;

Ticker flipper;
int count = 0;
bool blinking = true;

void flip() {
  //toggle led 
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));     

  count++;
  
  if (count == 10) {
    flipper.attach(0.1, flip);
  }
  else if (count >= 50) {
    flipper.detach();
    count=0;
  }
  Serial.println("in flip");
}

void buttonISR() {
    // langsames flip nach btn pres
    flipper.attach(1, flip);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);       
  pinMode(BUTTON_PIN, INPUT_PULLUP); 

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, CHANGE);
  
  // Starte das Blinken der LED
  flipper.attach(0.3, flip);
}

void loop() {
  //nothing to do for me :(
}