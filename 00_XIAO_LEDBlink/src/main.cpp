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
ESP32 LED Blink | V1.0 | 01.2024
*/
#include <Arduino.h>

byte led = D7;

void setup()
{
 Serial.begin(115200);
 pinMode(led, OUTPUT);
}
void loop()
{
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}
