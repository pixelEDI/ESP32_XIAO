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
ESP32 XIAO mit OLED 0,42 und DHT22 | V1.0 | 01.2024
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN D9
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float humidity = 0;
float temperature = 0;

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

unsigned long previousMillis = millis();

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  dht.begin();
}
void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= (1000 * 1))
  {
    display.clearDisplay();

    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    display.setCursor(35, 12);
    display.print("Temp:");
    display.println(String(temperature));

    display.setCursor(35, 24);
    display.print("Hum:");
    display.println(String(humidity));

    display.display();
  }
}