#include <gpio_viewer.h> // Must me the first include in your project
GPIOViewer gpio_viewer;
#include "credentials.h"

int gpio2 = D0;
int gpio3 = D1;
int gpio4 = D2;
int gpio5 = D3;
int gpio6 = D4;
int gpio7 = D5;
int gpio21 = D6;

int gpio20 = D7;
int gpio8 = D8;
int gpio9 = D9;
int gpio10 = D10;

int brightness = 0;
bool state = LOW;
unsigned long previousMillisLed = millis();
unsigned long previousMillisLedfade = millis();

void fading(unsigned long currMills){
  
  if (currMills - previousMillisLedfade >= 50) {
    // Speichere den Zeitpunkt der letzten Aktualisierung
    previousMillisLedfade = currMills;

    // Ändere die Helligkeit basierend auf dem aktuellen Zustand
    if (brightness < 255) {
      brightness++;
    } else {
      brightness = 0;
    }

    // Setze die PWM-Helligkeit
    analogWrite(gpio4, brightness);
  }
}

void setup()
{
  Serial.begin(115200);

  // Comment the next line, If your code aleady include connection to Wifi in mode WIFI_STA (WIFI_AP and WIFI_AP_STA are not supported)
  gpio_viewer.connectToWifi(ssid, password);
  // gpio_viewer.setPort(5555);   // You can set the http port, if not set default port is 8080

  // Your own setup code start here
  pinMode(gpio2, OUTPUT);
  pinMode(gpio3, OUTPUT);
  pinMode(gpio4, OUTPUT);
  pinMode(gpio5, OUTPUT);
  pinMode(gpio6, OUTPUT);
  pinMode(gpio7, OUTPUT);
  pinMode(gpio8, OUTPUT);
  pinMode(gpio9, OUTPUT);
  pinMode(gpio10, OUTPUT);
  pinMode(gpio20, OUTPUT);
  pinMode(gpio21, OUTPUT);

  // Must be at the end of your setup
  gpio_viewer.setSamplingInterval(50); // You can set the sampling interval in ms, if not set default is 100ms
  gpio_viewer.begin();
}

void loop(){
  
   unsigned long currentMillis = millis();
    if (currentMillis - previousMillisLed >= 1000) {
      previousMillisLed = currentMillis;
      state = !state;
      digitalWrite(gpio5, state);
      digitalWrite(gpio6, !state);

      digitalWrite(gpio9, HIGH);
    }

    fading(currentMillis);
}











