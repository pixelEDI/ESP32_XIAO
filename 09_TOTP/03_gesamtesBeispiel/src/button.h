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
Button Class | V1.0 | 02.2024
*/
#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button
{
protected:
    int btnPin;
    int state;
    int result;
    unsigned long buttonclickedMS;
    unsigned long buttonDownMS;

public:
    Button(int pin);
    int checkBTN();
    bool isPressed();
};

#endif