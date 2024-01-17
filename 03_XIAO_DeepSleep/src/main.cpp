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
ESP32 XIAO DeepSleep | V1.0 | 01.2024

https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/sleep_modes.html
*/
#include <Arduino.h>

unsigned long previousMillis = millis();
int cnt = 0;

void setDeepSleep()
{
  Serial.println("Going to sleep zzZZZzz");
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_OFF);
  ESP.deepSleep(20 * 1e6);
}

void setup()
{
  Serial.begin(115200);
}
void loop()
{

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= (1000 * 1))
  {
    previousMillis=currentMillis;
    cnt++;
    Serial.println(cnt);
  }

  if (cnt > 10)
  {
    cnt = 0;
    setDeepSleep();
  }
}