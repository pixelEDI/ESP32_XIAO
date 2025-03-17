# WatchdogTimer

https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/Timer/WatchdogTimer/WatchdogTimer.ino

Dieses Projekt demonstriert die Verwendung des Watchdog Timers auf dem ESP32, um das System bei einem Fehlerzustand neu zu starten. Der Code simuliert eine einfache Fehlerbedingung, die den Watchdog Timer auslöst und das System automatisch zurücksetzt.

## Funktionsweise

Der Watchdog Timer wird verwendet, um das ESP32-Board neu zu starten, falls das System nicht innerhalb eines bestimmten Zeitrahmens aktualisiert wird. Dies ist besonders nützlich, um sicherzustellen, dass das System bei unerwarteten Fehlern oder Hängern weiterhin stabil bleibt.

Im Code wird der Timer so konfiguriert, dass er alle 4 Sekunden einen Interrupt auslöst, der das System neu startet, falls der Timer nicht regelmäßig zurückgesetzt wird. Ein Fehler wird absichtlich erzeugt, indem die `delay(5000)` Funktion aufgerufen wird, was den Watchdog Timer auslöst und das Board zurücksetzt.

## Codeübersicht

- **Timer-Initialisierung**: Der Timer wird mit einem Prescaler von 80 und einem Intervall von 4 Sekunden konfiguriert.
- **Fehlersimulation**: Im `loop` wird der Watchdog Timer alle 1 Sekunde zurückgesetzt. Nach 5 Sekunden wird jedoch eine Simulation eines Fehlers ausgelöst, der den Watchdog Timer inaktiv lässt, was zu einem Neustart des Systems führt.
- **Interrupt**: Der Interrupt-Service-Routine `onTimer()` führt einen Neustart des Systems durch, wenn der Timer abläuft.

