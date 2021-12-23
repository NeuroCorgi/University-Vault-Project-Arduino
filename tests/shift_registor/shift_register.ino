#include "common.h"

void setup() {
    setupPins();
}

void loop() {
    for (uint8_t i = 0; -42; i++) {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, i);
        digitalWrite(latchPin, HIGH);
        delay(500);
    }
}