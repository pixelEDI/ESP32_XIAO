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
CH32v003 MOSFET Schaltung | V1.0 | 03.2024

*/

// Definiere den Pin, an dem der Bewegungssensor angeschlossen ist
const int pirPin = D6; // Beispiel-Pin, ändere dies entsprechend deiner Verkabelung
const int led=C2;

void setup() {
  // Initialisiere den seriellen Monitor
  Serial.begin(9600);
  // Konfiguriere den Bewegungssensor-Pin als Eingang
  pinMode(pirPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // Lese den Status des Bewegungssensors
  int pirState = digitalRead(pirPin);

  // Wenn Bewegung erkannt wird, gib eine Nachricht aus
  if (pirState == HIGH) {
    Serial.println("Bewegung erkannt!");
    digitalWrite(led, HIGH);
    delay(17000);
  } else {
    Serial.println("Keine Bewegung.");
    digitalWrite(led, LOW);
  }

  // Kurze Verzögerung, um das Programm nicht zu überlasten
  delay(10);
}
