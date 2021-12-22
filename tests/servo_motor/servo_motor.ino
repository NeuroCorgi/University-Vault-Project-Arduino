#include <Servo.h>
#include "common.h"

Servo test_servo;

void setup() {
    setupPins();
    test_servo.attach(servoPin);
}

void loop() {
    for (uint8_t pos = 0; pos < 180; pos++) {
        test_servo.write(pos);
        delay(5);
    }
    for (uint8_t pos = 180; pos > 0; pos--) {
        test_servo.write(pos);
        delay(5);
    }
}