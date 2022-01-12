/****************************************
 * common.h
 * Fort Knocks vault source code
 * 
 * Pinout
 ****************************************/

#ifndef COMMON_H
#define COMMON_H

// #define DEBUG

#ifdef DEBUG
#define debug(statement, ...) Serial.println(statement, ##__VA_ARGS__);
#else
#define debug(statement, ...)
#endif

/*
 * Servo pins
 */
#define servoPin 3
#define closeBtn A5
#define setBtn A4

/*
 * LEDs pins
 */

#define rLED 6
#define gLED 4

/*
 * Disply pins 
 */
#define clockPin 13
#define latchPin 12
#define dataPin 11
#define SSD1 10     // First seven segment display
#define SSD2 9      // Second seven segment display
#define SSD3 8      // Third seven segment display

/*
 * Rotary encoder pins
 */
#define pinCLK 7
#define pinDT 2
#define pinSW A0


/*
 * Alarm pins
 */
#define buzPin 5

/*
 * Set pin modes
 */
void setupPins() {
    Serial.begin(115200);
    
    pinMode(servoPin, OUTPUT);
    pinMode(closeBtn, INPUT_PULLUP);
    pinMode(setBtn, INPUT_PULLUP);

    pinMode(rLED, OUTPUT);
    pinMode(gLED, OUTPUT);

    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(latchPin, OUTPUT);

    pinMode(SSD1, OUTPUT);
    pinMode(SSD2, OUTPUT);
    pinMode(SSD3, OUTPUT);

    pinMode(pinCLK, INPUT_PULLUP);
    pinMode(pinDT, INPUT_PULLUP);
    pinMode(pinSW, INPUT_PULLUP);

    pinMode(buzPin, OUTPUT);
}

#endif /* COMMON_H */