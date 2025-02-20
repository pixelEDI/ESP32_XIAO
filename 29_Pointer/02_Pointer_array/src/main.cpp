
/*
       _          _          _ _
 _ __ (_)_  _____| | ___  __| (_)
| '_ \| \ \/ / _ \ |/ _ \/ _` | |
| |_) | |>  <  __/ |  __/ (_| | |
| .__/|_/_/\_\___|_|\___|\__,_|_|
|_|

https://links.pixeledi.eu
ESP32 Pointer | 01.2025

*/

#include <Arduino.h>

#define ARRAY_SIZE 40

int findMaxValue(int *arr, int size) {

  Serial.printf("sizeof *arr %zu \n", sizeof(arr));
  int maxValue = arr[0];

  for (int i = 1; i < size; i++) {
    if (arr[i] > maxValue) {
      maxValue = arr[i];
    }
  }
  return maxValue;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {

  unsigned long vergleichswert = millis();

  int messwerte[ARRAY_SIZE] = {12, 87, 23, 73, 34, 90,  23, 76, 54, 8,
                               29, 41, 2,  68, 77, 3,   94, 58, 10, 33,
                               82, 17, 21, 11, 59, 780, 39, 73, 62, 30,
                               19, 86, 5,  95, 74, 16,  27, 84, 50, 36};

  // int *ptr = messwerte;
  //
  // Serial.printf("sizeof messwerte %zu \n", sizeof(messwerte));
  // Serial.printf("sizeof *ptr %zu \n", sizeof(ptr));
  // Serial.printf("sizeof vergleichswert %zu \n", sizeof(vergleichswert));

  int size = sizeof(messwerte) / sizeof(messwerte[0]);
  int maxValue = findMaxValue(messwerte, size);
  Serial.printf("Höchste Messwert: %d \n", maxValue);

  delay(5000);
}
