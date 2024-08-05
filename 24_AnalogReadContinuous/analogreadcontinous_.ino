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
ESP32 AnalogReadContinuous Vergleich | V1.0 | 06.2024

https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/AnalogReadContinuous/AnalogReadContinuous.ino

*/
#define CONVERSIONS_PER_PIN 5
volatile bool adc_coversion_done = false;
adc_continuous_data_t *result = NULL;

// einzelauswertung
uint8_t adc_pin = 3;
uint8_t adc_pins[] = { 2, 3, 4 };  //ADC1 ESP32C3 XIAO
uint8_t adc_pins_count = sizeof(adc_pins) / sizeof(uint8_t);

unsigned long startTime;
unsigned long durationContinuous;
unsigned long durationSingle;

void ARDUINO_ISR_ATTR adcComplete() {
  adc_coversion_done = true;
}


void testContiniousReading(){

  //Messwert: für 3 pins ~ 30µs

  if (adc_coversion_done == true) {
    startTime = micros();
    
    adc_coversion_done = false;
    if (analogContinuousRead(&result, 0)) {

      durationContinuous = micros() - startTime;
      // Optional: Stop ADC Continuous conversions to have more time to process (print) the data
      analogContinuousStop();

     for (int i = 0; i < adc_pins_count; i++) {
        Serial.printf("\nADC PIN %d data:", result[i].pin);
        Serial.printf("\n   Avg raw value = %d", result[i].avg_read_raw);
        Serial.printf("\n   Avg millivolts value = %d", result[i].avg_read_mvolts);
      }

        Serial.printf("\n   Time for reading = %d", durationContinuous);
        Serial.printf("\n  -----------------");

      // Delay for better readability of ADC data
      delay(2000);

      // Optional: If ADC was stopped, start ADC conversions and wait for callback function to set adc_coversion_done flag to true
      analogContinuousStart();
    } else {
      Serial.println("Error occurred during reading data. Set Core Debug Level to error or lower for more information.");
    }
  }
}

void testSimpleAnalogRead() {
  //messwert: 32 µs
  startTime = micros();
  int val = analogRead(adc_pin);
  durationContinuous = micros() - startTime;
  Serial.printf("\n   AnalogRead Value = %d", val);
  Serial.printf("\n   Time for reading = %d", durationContinuous);
  delay(1000);
}

void testSimple3AnalogRead() {
  // messwert: 92 µs
  int analogValues[adc_pins_count];

  startTime = micros();
  for (int i = 0; i < adc_pins_count; i++) {
    analogValues[i] = analogRead(adc_pins[i]);
  }
  durationContinuous = micros() - startTime;

  for (int i = 0; i < adc_pins_count; i++) {

     Serial.print("Pin ");
     Serial.print(adc_pins[i]);
     Serial.print(": ");
     Serial.println(analogValues[i]);
  }
    Serial.printf("\n   Time for reading = %d", durationContinuous);
  Serial.printf("\n   ------------------- \n");
  delay(1000);

}

void setup() {
  Serial.begin(115200);

  analogContinuous(adc_pins, adc_pins_count, CONVERSIONS_PER_PIN, 20000, &adcComplete);
  analogContinuousStart();
}

void loop() {
  //testSimpleAnalogRead();
  //testSimple3AnalogRead();

  testContiniousReading();
}
