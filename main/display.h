/****************************************
 * display.h
 * Fort Knocks vault source code
 * 
 * Implementation of seven segment displays interface
 *
 * Created by: Aleksandr Pokatilov 516699@student.saxion.nl
 *         on: 09.12.2021
 ****************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "common.h"

#define previosSegment(pos) (pos == 0 ? SSD1 : (pos == 1 ? SSD3 : SSD2))
#define currentSegment(pos) (pos == 0 ? SSD3 : (pos == 1 ? SSD2 : SSD1))

/*
 * Global structure to store display data
 */
struct Display {
    uint32_t data;
    uint8_t active;
    uint8_t isOn;
} SSDISPLAY;

/*
 * Setup arduino timer interrupts to 1kHz
 */
void setupDisplayInterrupt() {
    // Enable timer compare interrupt
    TIMSK0 |= (1 << OCIE0A);
    // Enable interrupts
    sei();
}

/*
 * Resets Display struct to initial values 
 */
void resetDisplay(void) {
    SSDISPLAY.data = 0;         /* Display three zeros  */
    SSDISPLAY.active = 0b1111;  /* No active cursor     */
    SSDISPLAY.isOn = 1;         /* Display is on        */
}

/*
 * Update active display indication
 * @param pos new active position
 */
void updateActive(uint8_t pos) {
    SSDISPLAY.active = ~(1 << (2 - pos));
}

/*
 * Returns number for display pos
 * @param pos position of the digit to get
 * @return Number at digit away from the left
 */
uint8_t getDigit(uint8_t pos) {
    unsigned int data = SSDISPLAY.data;
    for (uint8_t i = 0; i < 2 - pos; i++) {
        data /= 10;
    }
    return data % 10;
}

/*
 * Update n_th digit of the output data to digit
 * @param n        position of digit in the data to change
 * @param digit    new digit
 */
void updateDigit(uint8_t n, uint8_t digit) {
    uint32_t data = 0;
    uint8_t pos = 1;
    uint32_t cur_data = SSDISPLAY.data;
    for (uint8_t i = 0; i < 3; i++) {
        if (i == 2 - n) { data += pos * digit; }
        else { data += cur_data % 10 * pos; }
        pos *= 10;
        cur_data /= 10;
    }
    SSDISPLAY.data = data;
}


/*
 * Update data to display with new data
 * @param data new data
 */
void updateData(uint32_t data) {
    SSDISPLAY.data = data;
}

/*
 * Return output for the current seven segment display
 * @param pos   number of seven segment display
 * @return First 4 bits is an active disply indication;
 * second 4 bits is number to display
 */
uint8_t getDisplayOutput(uint8_t pos) {
    return SSDISPLAY.active << 4 | getDigit(pos);
}

/*
 * Display data from SSDISPLAY struct on 3 seven segment displays or turn them off
 */
void display() {
    static char pos = 0;
    if (SSDISPLAY.isOn == 1) {
        digitalWrite(previosSegment(pos), LOW);                         /* Turn off previous seven segment display */
        /* Write data to the shift register */
        digitalWrite(latchPin, LOW);                                    /* Disable latch pin to store new data  */
        shiftOut(dataPin, clockPin, MSBFIRST, getDisplayOutput(pos));   /* Write data                           */
        digitalWrite(latchPin, HIGH);                                   /* Enable latch pin to save data        */
        digitalWrite(currentSegment(pos), HIGH);                        /* Turn on current seven segment display */
        
        pos++;      /* Increment position   */
        pos %= 3;   /* Loop it              */
    } else {
        /* Turn off all of the seven segment displays */
        for (uint8_t i = 0; i < 3; i++) {
            digitalWrite(currentSegment(i), LOW);
        }
    }
}

/*
 * Timer interrupt function to update seven segment displays
 */
SIGNAL(TIMER0_COMPA_vect) {
    display();
}

#endif /* DISPLAY_H */