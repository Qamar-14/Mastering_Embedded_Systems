/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "STM32F103C_Drivers/MCAL_Drivers/GPIO_DRIVER/gpio.h"
#include "STM32F103C_Drivers/HAL_Drivers/LCD_DRIVER/lcd.h"
#include "../../stm32/Src/STM32F103C_Drivers/MCAL_Drivers/EXTI_DRIVER/ext_interrupt.h"

void clock_init()
{

	//Enable clock GPIOA
	RCC_GPIOA_CLK_EN();
	//RCC_GPIOB_CLK_EN();
}

int main(void)
{
	clock_init();

	LCD_INIT();
	LCD_WRITE_STRING("Qamar Elgohary");
	for (int i = 0; i < 500000; i++);
	DISPLAY_NUMBER(22);
	for (int i = 0; i < 500000; i++);
	for (int i = 0; i < 500000; i++);
	LCD_clear_screen();
	DISPLAY_REAL_NUMBER(100.5);
	return 0;
}


