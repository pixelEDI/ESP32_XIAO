# AnalogReadContiniuous
AnalogReadContinuous für ESP32 bietet folgende Vorteile gegenüber normalen AnalogRead:
- Kontinuierliche Messungen: Es ermöglicht kontinuierliche Erfassung analoger Werte, ohne dass wiederholte Aufrufe erforderlich sind.
- Zeitersparnis: Spart Zeit und Ressourcen, da es schnell und effizient eine kontinuierliche Datenstrom liefert.
- Echtzeit-Anwendungen: Ideal für Echtzeit-Anwendungen, die schnelle und präzise analoge Eingaben erfordern, ohne Unterbrechungen für wiederholte Messungen.
    
Original Beispiel: https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/AnalogReadContinuous/AnalogReadContinuous.ino

## Code Beispiel

* Für testContiniousReading() im Setup die beiden auskommentierten Funktionen aktivieren.
* Im Loop kann gewechselt werden zwischen AnalogRead und AnalogReadContiniuous

