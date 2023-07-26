/*
 *
 * Keypad_driver.h
 *
 *
 *	Created on: 7/23/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define F_CPU 1000000UL

//-------------------------------------------------
// INCLUDES
//-------------------------------------------------


#include "../../MCAL_Drivers/GPIO_DRIVER/gpio.h"

#define KEYPAD_PORT GPIOB

#define R0 GPIO_PIN0
#define R1 GPIO_PIN1
#define R2 GPIO_PIN3
#define R3 GPIO_PIN4
#define C0 GPIO_PIN5
#define C1 GPIO_PIN6
#define C2 GPIO_PIN7
#define C3 GPIO_PIN8

//-------------------------------------------------
// KEYPAD FUNCTIONS
//-------------------------------------------------


void KEYPAD_INIT(void);

unsigned char KEYPAD_GET_KEY(void);

#endif
