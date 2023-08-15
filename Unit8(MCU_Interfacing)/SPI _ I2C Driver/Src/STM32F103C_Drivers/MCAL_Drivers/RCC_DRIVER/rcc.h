/*
 *
 * STM32F103x8_RCC_driver.h
 *
 *
 *	Created on: 7/15/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */
#ifndef INC_STM32F103x8_RCC_DRIVER_H_
#define INC_STM32F103x8_RCC_DRIVER_H_

//-------------------------------------------------
// INCLUDES
//-------------------------------------------------
#include <STM32F103.h>
#include "GPIO_DRIVER/gpio.h"


//-------------------------------------------------
// MACROS
//-------------------------------------------------
#define HSI_CLK		(uint32_t)16000000
#define HSE_CLK		(uint32_t)8000000

//-------------------------------------------------
// APIs supported by "MCAL RCC DRIVER"
//-------------------------------------------------

uint32_t MCAL_RCC_GET_SYSCLK_FREQ		(void);
uint32_t MCAL_RCC_GET_HCLK_FREQ		    (void);
uint32_t MCAL_RCC_GET_PCLK1_FREQ		(void);
uint32_t MCAL_RCC_GET_PCLK2_FREQ		(void);




#endif
