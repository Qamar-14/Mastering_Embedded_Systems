/*
 *
 * STM32F103x8_GPIO_driver.h
 *
 *
 *	Created on: 7/22/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */

#ifndef INC_STM32F103x8_GPIO_DRIVER_H_
#define INC_STM32F103x8_GPIO_DRIVER_H_

//-------------------------------------------------
// INCLUDES
//-------------------------------------------------

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <STM32F103.h>

//-------------------------------------------------
// CONFIG STRUCTURES
//-------------------------------------------------

typedef struct
{

	uint16_t GPIO_PIN_NO; // Specifies the gpio pins to be configured
				// This parameter can be a value of @ref GPIO_PINS_DEFINE

	uint8_t GPIO_MODE;      // Specifies the gpio mode for selected pin
				// This parameter can be a value of @ref GPIO_MODE_DEFINE

	uint8_t GPIO_OUTPUT_SPEED; // Specifies the speed for selected pin (output mode)
				   // This parameter can be a value of @ref GPIO_SPEED_DEFINE


}GPIO_PIN_CONFIG_t;

//-------------------------------------------------
// @ref
//-------------------------------------------------

/*
	GPIO_PIN_SATE
*/

#define GPIO_PIN_SET		1
#define GPIO_PIN_RESET		0

/*
	GPIO_RETURN_LOCK
*/

#define GPIO_RETURN_LOCK_EN			1
#define GPIO_RETURN_LOCK_ERROR		0

/*
	GPIO_PIN_DEFINE
*/

#define GPIO_PIN0		((uint16_t)0x0001u) //PIN 0 selected
#define GPIO_PIN1		((uint16_t)0x0002u) //PIN 1 selected
#define GPIO_PIN2		((uint16_t)0x0004u) //PIN 2 selected
#define GPIO_PIN3		((uint16_t)0x0008u) //PIN 3 selected
#define GPIO_PIN4		((uint16_t)0x0010u) //PIN 4 selected
#define GPIO_PIN5		((uint16_t)0x0020u) //PIN 5 selected
#define GPIO_PIN6		((uint16_t)0x0040u) //PIN 6 selected
#define GPIO_PIN7		((uint16_t)0x0080u) //PIN 7 selected
#define GPIO_PIN8		((uint16_t)0x0100u) //PIN 8 selected
#define GPIO_PIN9		((uint16_t)0x0200u) //PIN 9 selected
#define GPIO_PIN10		((uint16_t)0x0400u) //PIN 10 selected
#define GPIO_PIN11		((uint16_t)0x0800u) //PIN 11 selected
#define GPIO_PIN12		((uint16_t)0x1000u) //PIN 12 selected
#define GPIO_PIN13		((uint16_t)0x2000u) //PIN 13 selected
#define GPIO_PIN14		((uint16_t)0x4000u) //PIN 14 Selected
#define GPIO_PIN15		((uint16_t)0x8000u) //PIN 15 selected
#define GPIO_PIN_ALL	((uint16_t)0xFFFFu) //All pins selected

#define GPIO_PIN_MASK		0x0000FFFFU //Pin mask for assert test

/*
  GPIO_MODE_DEFINE
	0:	Analog Mode
	1:	Floating input (reset)
	2:	Input with pull up
	3:	Input with pull down
	4:	General purpose output push-pull
	5:	General purpose output open-drain
	6:	Alternate purpose output push-pull
	7:	Alternate purpose output open-drain
	8:	Alternate function input
*/

#define GPIO_MODE_ANALOG			0x00000000U //Analog mode
#define GPIO_MODE_INPUT_FLOATING	0x00000001U //Floating input (reset)
#define GPIO_MODE_INPUT_PU			0x00000002U //Input with pull up
#define GPIO_MODE_INPUT_PD			0x00000003U //Input with pull down
#define GPIO_MODE_OUTPUT_PP			0x00000004U //General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD			0x00000005U //General purpose output open-drain
#define GPIO_MODE_OUTPUT_AF_PP		0x00000006U //Alternate purpose output push-pull
#define GPIO_MODE_OUTPUT_AF_OD		0x00000007U //Alternate purpose output open-drain
#define GPIO_MODE_AF_INPUT			0x00000008U //Alternate function input

/*
  GPIO_SPEED_DEFINE
	00:	MAX SPEED 10MHZ
	01:	MAX SPEED 20MHZ
	10:	MAX SPEED 50MHZ

*/

#define GPIO_SPEED_10MHZ			0x00000001U //10 MHZ
#define GPIO_SPEED_2MHZ				0x00000002U //2  MHZ
#define GPIO_SPEED_50MHZ			0x00000003U //50 MHZ



//-------------------------------------------------
// APIs supported by "MCAL GPIO DRIVER"
//-------------------------------------------------

void MCAL_GPIO_Init	(GPIO_Typedef *GPIOx , GPIO_PIN_CONFIG_t* PINconfig);
void MCAL_GPIO_DeInit	(GPIO_Typedef *GPIOx);

/* READ APIs */

uint8_t MCAL_GPIO_READ_PIN 	(GPIO_Typedef *GPIOx , uint16_t PIN);
uint16_t MCAL_GPIO_READ_PORT	(GPIO_Typedef *GPIOx);

/* WRITE APIs */

void MCAL_GPIO_WRITE_PIN 	(GPIO_Typedef  *GPIOx, uint16_t PIN , uint8_t value);
void MCAL_GPIO_WRITE_PORT	(GPIO_Typedef *GPIOx, uint8_t value);

void MCAL_GPIO_TOGGLE_PIN 	(GPIO_Typedef *GPIOx , uint16_t PIN);

uint8_t MCAL_GPIO_LOCK_PIN 	(GPIO_Typedef *GPIOx , uint16_t PIN);

void MCAL_GPIO_SET_PIN_OUTPUT(GPIO_Typedef *GPIOx, uint16_t PIN, uint8_t MODE, uint8_t SPEED);
void MCAL_GPIO_SET_PIN_INPUT(GPIO_Typedef *GPIOx, uint16_t PIN, uint8_t MODE);


#endif
