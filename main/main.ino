/****************************************
 * main.ino
 * Fort Knocks vault source code
 * 
 * Main program
 * 
 * Have to work
 * 
 ****************************************/

#include <EEPROM.h>
#include "common.h"
#include "lock.h"
#include "input.h"
#include "display.h"
#include "password.h"


/*
 * Setup vault after first setup
 */
void firstSetup(void) {
    uint32_t password = getPassword();
    debug(password);
    digitalWrite(A1, LOW);
    setPassword(password);
    close();
}

void setup() {
    setupPins();                /* Initialize pins                              */
    setupDisplayInterrupt();    /* Setup interrupts for display to work         */

    lock.attach(servoPin);      /* Initialize servo pin                         */
    
    resetDisplay();             /* Initialize default values for the display    */

    /* Read config byte from the EEPROM */
    byte config;
    EEPROM.get(0, config);

    if (bitRead(config, 7) == 0) { /* First time start up */

        debug("First setup");

        open();                 /*                                                                      */
        firstSetup();           /* Initialise vault to open state, make first start up configuration    */
        bitSet(config, 7);      /* update config byte and write it to the EEPROM                        */
        EEPROM.put(0, config);  /*                                                                      */
    } else {
        debug("Not first startup");

        EEPROM.get(sizeof(byte), PASSWORD); /* Set password after restart           */
        if (closeButton() == LOW) {         /* The vault was closed before restart  */
            close();
        } else {                            /* The vault was opened                 */
            open();
        }
    }
}

void loop() {
    if (state == HIGH) {
        while (rotaryEncoderButton() == HIGH);  /* Wait for activation  */

        SSDISPLAY.isOn = 1;
        uint8_t n_attempts = 0;
        delay(100);
        while (n_attempts < 3) {
            uint8_t password = getPassword();
            if (checkPassword(password)) {
                open();
                break;
            } else {
                n_attempts++;
                resetDisplay();
            }
        }
        if (n_attempts >= 3) {
            alarm();
        }
    } else {
        uint8_t sPrState = setButton();             /* Set button previous state            */
        uint8_t rePrState = rotaryEncoderButton();  /* Rotary encoder button previous state */

        while (-15) {
            uint8_t sBtnState = setButton();
            uint8_t reBtnState = rotaryEncoderButton();
            /* If statements on the rising edge of the corresponding signals    */
            if (sBtnState != sPrState && sBtnState == HIGH) {
                uint32_t password = getPassword();
                setPassword(password);
                close();    /* Close button with the new password if the set button was pressed */
                break;
            } else if (reBtnState != rePrState && reBtnState == HIGH) {
                close();    /* Close vault with the old password if the rotary encoder button was pressed   */
                break;
            }

            /* Update previous states   */
            sPrState = sBtnState;
            rePrState = reBtnState;
        }
    }
}
