
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
ESP32 Pointer | 01.2025

*/

#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  delay(1000);
}
void loop() {
  int eineVariable = 74;
  int *einPointer = &eineVariable;

  Serial.printf("eineVariable: %d einPointer: %d \n", eineVariable,
                *einPointer);

  Serial.printf("Speicheradresse eineVariable: %p \n", (void *)&eineVariable);
  Serial.printf("Zieladresse von *einPointer: %p \n", (void *)einPointer);
  Serial.printf("Speicheradresse von *einPointer: %p \n",
                (unsigned int)&einPointer, HEX);

  delay(3000);
}
