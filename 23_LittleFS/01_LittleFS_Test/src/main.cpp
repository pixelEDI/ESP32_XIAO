/*
        _          _ ______ _____ _____
       |_|        | |  ____|  __ \_   _|
  _ __  ___  _____| | |__  | |  | || |
 | '_ \| \ \/ / _ \ |  __| | |  | || |
 | |_) | |>  <  __/ | |____| |__| || |_
 | .__/|_/_/\_\___|_|______|_____/_____|
 | |
 |_|

https://links.pixeledi.eu
LittleFS | V1.0 | 07.2024
*/

#include <Arduino.h>
#include <LittleFS.h>

unsigned long previousMillis = 0;
String webserverText = "Warte auf Input";
bool updateText = false;

void writeLittleFSFile() {
  File file = LittleFS.open("/messdaten.txt", "a");
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }

  unsigned long currentSeconds = millis() / 1000;

  file.println(currentSeconds);
  file.close();
}

void   readLittleFSFile(){
  File file = LittleFS.open("/messdaten.txt", "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  while (file.available()) {
    Serial.write(file.read());
  }

  file.close();
}

void setup()
{
  Serial.begin(115200);

  if (!LittleFS.begin())
  {
    Serial.println("LittleFS mount failed");
    return;
  }

}

void loop()
{
  delay(3000);
  writeLittleFSFile();
  readLittleFSFile();
}
