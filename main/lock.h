/****************************************
 * lock.h
 * Fort Knocks vault source code
 * 
 * Lock functions
 *
 * Created by: Stephen Cruz Wright 521476@student.saxion.nl
 *         on: 09.12.2021
 ****************************************/

#ifndef LOCK_H
#define LOCK_H

#include <Arduino.h>
#include <Servo.h>
#include "common.h"
#include "alarm.h"
#include "input.h"
#include "display.h"
#include "password.h"

#define OPEN_ANGLE 0
#define CLOSE_ANGLE 90

Servo lock; /* Servo motor to lock */

uint8_t state = LOW; /* State: LOW - opened; HIGH - closed */

/*
 * Turn on or off indicator LEDs according to current state
 */
void turnIndicatorLEDs() {
    digitalWrite(rLED, state);
    digitalWrite(gLED, !state);
}

/*
 * Main function to close the vault
 */
void close() {
    if (closeButton() == HIGH) { /* If the door is not closed play alarm sound */
        debug("Door not closed");
        playSound(0);
    }
    while (closeButton() == HIGH);
    stopSound(); /* Stop alarm when the door is closed */

    lock.write(CLOSE_ANGLE); /* Close the lock */

    debug("Closed");

    state = HIGH; /* Change state to closed */

    turnIndicatorLEDs();
    if (millis() > 1000) updateData(PASSWORD);  /* Do not display password if there is a restart */
    delay(2000);                                /* Remind user what the password is             */
    resetDisplay();
    SSDISPLAY.isOn = 0; /* Disable display when the vault is closed */
}

/*
 * Main function to open the vault
 */
void open() {
    lock.write(OPEN_ANGLE); /* Open the lock */

    debug("Opened");

    state = LOW; /* Change state to opened */

    resetDisplay();
    turnIndicatorLEDs();
}

#endif /* LOCK_H */