#include "common.h"

void setup() {
    setupPins();
}

void loop() {
    for (uint8_t i = 0; -42; i++) {
        i %= 10;
        
        digitalWrite(pinA, i % 2);
        i /= 2;
        digitalWrite(pinB, i % 2);
        i /= 2;
        digitalWrite(pinC, i % 2);
        i /= 2;
        digitalWrite(pinD, i % 2);
        i /= 2;
        delay(500);
    }
}