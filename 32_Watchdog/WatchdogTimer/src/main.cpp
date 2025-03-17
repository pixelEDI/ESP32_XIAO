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
WatchdogTimer | 03.2025

*/

#include <Arduino.h>
hw_timer_t *timer = NULL;
byte cnt = 0;

void IRAM_ATTR onTimer() {
  // ich werde neugestartet
  ESP.restart();
}

void setup() {
  Serial.begin(115200);

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, (1000000 * 4), true);
  timerAlarmEnable(timer);
}
void loop() {
  cnt++;
  Serial.println("feed the watchdog");
  timerWrite(timer, 0);
  delay(1000);

  if (cnt >= 5) {
    // fehler simulieren
    Serial.println("Ich bin ein Fehler - keine Macht dem Watchdog");
    delay(5000);
    Serial.println("Ich werde nicht mehr ausgegeben");
  }
}
