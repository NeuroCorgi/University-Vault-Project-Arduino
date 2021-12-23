#include "common.h"

void setup() {
    setupPins();
}

void loop() {
    static int state = LOW;
    static int previousButtonState;
    int buttonState = digitalRead(buttonPin);

    if (buttonState == LOW && buttonState != previousButtonState) {
        state = !state;
    }

    digitalWrite(ledPin, state);
}