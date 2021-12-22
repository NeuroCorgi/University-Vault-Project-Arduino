/****************************************
 * password.h
 * Fort Knocks vault source code
 * 
 * Interactions with password 
 *
 * Created by: Aleksandr Pokatilov 516699@student.saxion.nl
 *         on: 09.12.2021
 ****************************************/

#ifndef PASSWORD_H
#define PASSWORD_H

#include <Arduino.h>
#include <EEPROM.h>
#include "common.h"

uint32_t PASSWORD;

/*
 * Check if passed password is equal to stored password
 * @param password  password to check
 * @return if passwords are the same, 0 otherwise
 */
uint8_t checkPassword(uint32_t password) {
    return password == PASSWORD;
}

/*
 * Set new password and write it to the EEPROM
 * @param   new password
 * @return None
 */
void setPassword(uint32_t password) {
    PASSWORD = password;
    EEPROM.write(sizeof(char), PASSWORD); /* Write password adter configuration byte    */
}

#endif /* PASSWORD_H */