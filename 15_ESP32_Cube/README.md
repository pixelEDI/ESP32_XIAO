
## Library:
https://github.com/playfultechnology/esp32-smartcube/blob/master/esp32-smartcube.ino
https://arduinojson.org/v7/how-to/install-arduinojson/

* MAC Adresse finden
* Original Sketch adaptieren
 - const char* faceNames[6] = {"Front", "Bottom", "Right", "Top", "Left", "Back"};
 - In der Funktion bool connectToServer() am Ende "return true"
 - LED_BUILTIN auskommentieren
 - Anpassen - wann Cube gelöst: const byte solution[16] = {0x12, 0x38, 0x56, 0x74, 0x13, 0x32, 0x33, 0x31, 0x12, 0x34, 0x56, 0x79, 0x8a, 0xbc, 0x01, 0x80};
* Partition Scheme -> Huge App

## App zum finden der MAC Adresse
https://www.nordicsemi.com/Products/Development-tools/nrf-connect-for-mobile 


