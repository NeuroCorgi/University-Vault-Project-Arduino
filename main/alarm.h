/****************************************
 * Alarm.h
 * Fort Knocks vault source code
 * 
 * Basic functions of alarm system of the vault 
 *
 * Created by: Maciej Kolinski 510887@student.saxion.nl
 *         on: 09.12.2021
 ****************************************/

#ifndef ALARM_H
#define ALARM_H

#include <Arduino.h>
#include "common.h"
#include "lock.h"
#include "display.h"

/*
 * Play alarm sound for duration milliseconds of until stopSound is called
 * @param duration duration of alarm, 0 to play infinitely
 */
void playSound(uint32_t duration) {
    if (duration == 0) tone(buzPin, 400);
    else tone(buzPin, 400, duration);
}

/*
 * Stop alarm sound after 'playSound(0);'
 */
void stopSound() {
    noTone(buzPin);
}

/*
 * Main alarm function to call after 3 attempts of inputting password
 */
void alarm() {
    /* play alarm sound for 1 second */
    debug("Alarm");
    playSound(1000);

    /* Start the countdown until the next attempt will be possible */
    uint8_t time = 60;                 /* Countdown time */
    while (time > 0) {
        updateData(time);
        debug(time);
        delay(1000); 
        time--; /* Decrement 'time' var if one second has passed */
    }

    debug("Stop alarm");

    updateData(0);
    updateActive(0);
}

#endif /* ALARM_H */