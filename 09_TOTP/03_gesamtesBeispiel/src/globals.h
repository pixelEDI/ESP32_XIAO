#include <Arduino.h>
#include <totp.h>
#include <sha1.h>
#include <BleKeyboard.h>
#ifndef GLOBALS_
#define GLOBALS_

unsigned long previousMillis = millis();

float batteryleft=50;

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 0; // 3600 * 2; // gmt+2

TOTP totp;
BleKeyboard bleKeyboard("pixelPASS", "pixelEDI", batteryleft);

enum states {
  GETNEWDATA,
  SHOWDATA,
  WAIT
} state;

struct websites{
  String name;
  String secretkey;
  String onetimepw;
  time_t unixtimestamp;
};

byte chosenWebsite=0;
const byte arraylength=2;
websites myWebsites[arraylength];


// 'bluetooth(1)', 16x16px
//https://www.flaticon.com/free-icons/bluetooth" title="bluetooth icons">Bluetooth icons created by Lizel Arina - Flaticon
const unsigned char bluetooth_connected_grafic [] PROGMEM = {
	0x00, 0x00, 0x01, 0x80, 0x01, 0xc0, 0x01, 0xe0, 0x09, 0xb0, 0x0d, 0xb0, 0x07, 0xe0, 0x03, 0xc0, 
	0x03, 0xc0, 0x07, 0xe0, 0x0d, 0xb0, 0x09, 0xb0, 0x01, 0xe0, 0x01, 0xc0, 0x01, 0x80, 0x00, 0x00
};

#endif