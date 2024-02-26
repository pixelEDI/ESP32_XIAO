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
ESP32 2FA-App -> TOTP | V1.0 | 02.2024

Library example
https://github.com/fatlab101/arduino_totp/tree/master
https://github.com/fatlab101/arduino_totp/blob/master/examples/totp_basic/totp_basic.ino
*/

#include "credentials.h"
#include <WiFi.h>
#include <time.h>
#include <sha1.h>
#include <totp.h>
#include <BleKeyboard.h>
#include "button.h"

unsigned long previousMillis = millis();
BleKeyboard bleKeyboard("pixelPASS_DEV", "pixelEDI", 73);
Button btn(D8);
long code = 0;

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 0; // 3600 * 2; // gmt+2

TOTP totp = TOTP("OBJTOJLUIZKGEWTZJBBFGPC5JY7GQKK2");
char totpCode[7]; // get 6 char code

void checkButton()
{
  switch (btn.checkBTN())
  {
  case 1:
    // zum switchen der Website
    break;
  case 2:
    bleKeyboard.print(String(code));
    Serial.println("loooong click");
    delay(300);
    break;
  }
}

time_t printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
  }
  time_t unixTime = mktime(&timeinfo);
  Serial.println(unixTime);
  Serial.println(&timeinfo);

  return unixTime;
}

void setup()
{
  Serial.begin(115200);
  bleKeyboard.begin();
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  // nur 1x pro start wird die Zeit synchronisiert
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{

  checkButton();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= (1000 * 1))
  {

    time_t unixt = printLocalTime();
    code = totp.gen_code(unixt);
    Serial.print("timestamp = ");
    Serial.print(unixt);
    Serial.print(", magic number = ");
    Serial.print(code);
    totp.code_to_str(code, totpCode);
    Serial.print(", magic number str = ");
    Serial.println(totpCode);
  }
}
