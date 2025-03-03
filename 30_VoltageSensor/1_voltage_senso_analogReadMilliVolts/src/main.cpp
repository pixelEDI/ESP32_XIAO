
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

#include <Arduino.h>

const int voltageSensorPin = A2;
float vin = 0.0;
float vmeasure = 0.0;
int voltageSensorVal = 0;
float vcc = 3.3;
const float spannungsteilerfactor = 5;

unsigned long previousMillis = 0;

void setup() { Serial.begin(115200); }

void calcVin() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;

    vin = 0;
    for (int i = 0; i < 16; i++) {
      vin = vin + analogReadMilliVolts(voltageSensorPin);
    }

    vmeasure = spannungsteilerfactor * vin / 16 / 1000.0;
    Serial.println(vmeasure);
  }
}
void loop() { calcVin(); }
