#include "leds.h"
#include <Arduino.h>

leds::leds(int pin) {
  pinLED = pin;
  pinMode(pinLED, OUTPUT);
}

void leds::turnOn() {
  digitalWrite(pinLED, HIGH);
}

void leds::turnOff() {
  digitalWrite(pinLED, LOW);
}

// void leds::toggle() {
//   digitalWrite(pinLED, !digitalRead(pinLED));
// }

void leds::turnOffAfterDelay(int millisec, bool analogOff) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisAusschalten <= (millisec)) {
    // kein zurücksetzen von previousmillis
    // Dieser Abschnitt soll nur 1x pro Aufruf ausgeführt werden.

    // man könnte mit dieser Funktion auch die LED einschalten...
    // digitalWrite(pinLED, HIGH);
  } else {
    turnOff();
  }
}

void leds::fadeOn(int millisec) {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisFadeOn >= millisec) {
    previousMillisFadeOn = currentMillis;

    if (brightness <= 255) {

      digitalWrite(pinLED, HIGH);
      delayMicroseconds(brightness);
      digitalWrite(pinLED, LOW);
      delayMicroseconds(255 - brightness);
      brightness += fadeAmount;
    } else {
      digitalWrite(pinLED, LOW);
      delayMicroseconds(255);
    }
  }
}

void leds::pulsate(int delay_ms) {

    unsigned long currentMillis = millis();

  if (currentMillis - previousMillisPulsate >= delay_ms) {
    previousMillisPulsate = currentMillis;

    brightness += fadeDirection * fadeAmount;

    // Reverse the fade direction when reaching brightness limits
    if (brightness <= 0 || brightness >= 255) {
      fadeDirection = -fadeDirection;
    }

    digitalWrite(pinLED, HIGH);
    delayMicroseconds(brightness);
    digitalWrite(pinLED, LOW);
    delayMicroseconds(255 - brightness);
  } else {
    digitalWrite(pinLED, LOW);
    delayMicroseconds(255);
  }
}