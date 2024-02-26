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

Library TOTP & example
https://github.com/fatlab101/arduino_totp/tree/master
https://github.com/fatlab101/arduino_totp/blob/master/examples/totp_basic/totp_basic.ino

BLE Library
https://github.com/T-vK/ESP32-BLE-Keyboard
*/

#include "globals.h"
#include <WiFi.h>
#include <time.h>
#include <sha1.h>
#include <totp.h>
#include "oled.h"
#include "wifi_ntp.h"
#include "button.h"

char totpCode[7]; // platzhalter für Stringkonvetierung
Button btn(D8);

void setTOTPWebsiteData()
{
  // größe von struct muss in globals angepasst werden
  myWebsites[0].name = "Arduino";
  myWebsites[0].secretkey = "aaabbbcccdddd";
  myWebsites[0].onetimepw = "";

  myWebsites[1].name = "Proton";
  myWebsites[1].secretkey = "eeeeffffggghhhh";
  myWebsites[1].onetimepw = "";
}

String addLeadingZeros(int totp_code)
{
  String numStr = String(totp_code);
  while (numStr.length() < 6)
  {
    numStr = "0" + numStr;
  }
  return numStr;
}

void checkButton()
{
  switch (btn.checkBTN())
  {
  case 1:
    // loop through array by iterating
    if (chosenWebsite < (arraylength - 1))
    {
      chosenWebsite++;
    }
    else
    {
      chosenWebsite = 0;
    }
    break;
  case 2:
    // long press
    if (bleKeyboard.isConnected())
    {
      bleKeyboard.print(myWebsites[chosenWebsite].onetimepw);
      // show also on oled
      delay(300);
    }
    Serial.println("looooooooong click");

    break;
  }
}

void setup()
{
  Serial.begin(115200);

  startOled();
  showReady();

  setTOTPWebsiteData();

  readBatteryVoltage();
  bleKeyboard.begin();
  connectAP();
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  // nur 1x pro start wird die Zeit synchronisiert
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{

  unsigned long currentMillis = millis();
  checkButton();

  switch (state)
  {
  case GETNEWDATA:
    if (currentMillis - previousMillis >= (1000 * 1))
    {
      previousMillis = millis();
      time_t unixt = printLocalTime();
      myWebsites[chosenWebsite].unixtimestamp = unixt;

      String secretKey = myWebsites[chosenWebsite].secretkey;
      totp = TOTP(secretKey.c_str()); // Umweg über String to const char*
      
      String ttop_withLeadingZeros = addLeadingZeros(totp.gen_code(unixt));

      myWebsites[chosenWebsite].onetimepw = ttop_withLeadingZeros;
    }
    state = SHOWDATA;
    break;
  case SHOWDATA:
    showTTOP();
    isBLEConnected();
    showTimeLine();
    state = GETNEWDATA;
    break;
  }
}
