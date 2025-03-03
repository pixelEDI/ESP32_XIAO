#ifndef leds_h
#define leds_h

#include <Arduino.h>

class leds {
    //kein digitalWrite und analogWrite während eines Funktionsablaufs mixen!
  private:
    int pinLED;
    int brightness=0;
    int fadeAmount=5;
    int fadeDirection=1;
    bool pulsateMode=true;
    unsigned long previousMillis = 0;
    unsigned long previousMillisAusschalten = 0;
    unsigned long previousMillisPulsate=0;
    unsigned long previousMillisFadeOn=0;
    unsigned long previousMillisFadeOff=0;

  public:
    leds(int pin);
    void turnOn();
    void turnOff();
    void fadeOn(int millisec);
    void toggle();
    void flash(int delay_ms);
    void turnOffAfterDelay(int millisec, bool analogOff);
    void pulsate(int delay_ms);
    void setPulsateMode(bool val);
};

#endif