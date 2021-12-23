/****************************************
 * input.h
 * Fort Knocks vault source code
 * 
 * Input devices' reader functions
 *
 * Created by: Hoang Minh Lê 511907@student.saxion.nl
 *         on: 09.12.2021
 ****************************************/

#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include "display.h"
#include "common.h"

/*
 * Incapsulte digital read from the close button pin
 * @return digitalRead(close button pin)
 */
uint8_t closeButton() {
    return digitalRead(closeBtn);
}

/*
 * Incapsulte digital read from the set button pin
 * @return HIGH on rising edge of the set button pin
 */
uint8_t setButton() {
    return digitalRead(setBtn);
}

/*
 * Incapsulte digital read from the rotaru encoder button pin
 * @return HIGH on rising edge of the rotary encoder button pin
 */
uint8_t rotaryEncoderButton() {
    return digitalRead(pinSW);
}

/*
 * Main function to get password
 * @return password entered by user through the rotary encoder
 */
uint32_t getPassword() {
    uint32_t password = 0;

    uint8_t pas_CLK = 0;    /* Rotary encoder clock pin previous state  */
    uint8_t pas_DT = 0;     /* Rotary encoder data pin previous state   */
    uint8_t count = 0;      /* Position of the rotary encoder           */
    uint8_t rePrState;      /* Rotary encoder button previous state     */
    uint8_t sPrState;       /* Set button previous state                */
    uint8_t pos = 0;        /* Position of the input                    */
    updateActive(pos);
    rePrState = rotaryEncoderButton();
    sPrState = setButton();

    while (-42) {
        uint8_t CLK = digitalRead(pinCLK);  /* Rotary encoder clock current state   */
        uint8_t DT = digitalRead(pinDT);    // Rotary encoder pin current state     */

        /* On falling edge of the clock pin */
        if (CLK != pas_CLK && CLK == 0) {

            debug("Clock fall");
        
            if (pas_DT | DT == HIGH) { /* If the falling edge of the data pin was earlier */
                /* Counter clockwise */
                if (count == 0) count = 9; /* Loop count */
                else count--;

                debug("Counter clockwise");
                debug(count);
            } else {
                /* Clockwise */
                count++;
                count %= 10; /* Loop count */

                debug("Clockwise");
                debug(count);
            }
            updateDigit(pos, count);
        }

        /* Update previous states of the rotary encoder pins */
        pas_CLK = CLK;
        pas_DT = DT;

        /* Increment position on rising edge of the rotary encoder button */
        uint8_t reBtnState = rotaryEncoderButton();
        if (reBtnState != rePrState && reBtnState == HIGH) {
            debug("Rotary encoder button push");

            password = password * 10 + count;   /* Update digit in password */
            pos++;                              /* Move cursor forward      */
            updateActive(pos);                  /* Update active display    */
            count = 0;
            delay(10);                          /* Debouncing               */
        }

        /* Decrement position on rising edge of the set button */
        uint8_t sBtnState = setButton();
        if (sBtnState != sPrState && sBtnState == HIGH) {
            debug("Set button push");

            if (pos > 0) {
                updateDigit(pos, 0); /* Erase data for current digit            */
                password /= 10;      /* Erase last digit of the password        */
                pos--;               /* Move cursor back                        */
                updateActive(pos);   /* Update active display to match cursor   */
                count = getDigit(pos);
                delay(10);          /* Debouncing                              */
            }
        } 
        
        /* Update previos states of the buttons */
        rePrState = reBtnState;  
        sPrState = sBtnState;
        
        /* if password was entered, return it */
        if (pos == 3) return password;
    }
}

#endif /* INPUT_H */