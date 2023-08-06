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


typedef volatile unsigned int vuint32_t ;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// register address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)

//APB2 peripheral clock enable register (RCC_APB2ENR)
#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)
#define RCC_CFGR *(volatile uint32_t *)(RCC_BASE + 0x04)

void clockINIT ()
{


/*Bits 1:0 SW[1:0]: System clock Switch
Set and cleared by software to select SYSCLK source.
Set by hardware to force HSI selection when leaving Stop and Standby mode or in case of failure of
the HSE oscillator used directly or indirectly as system clock (if the Clock Security System is
enabled).
00: HSI selected as system clock
01: HSE selected as system clock
10: PLL selected as system clock
11: Not allowed*/

	RCC_CFGR|= (1<<0);


	/*Bit 16 PLLSRC: PLL entry clock source
Set and cleared by software to select PLL clock source. This bit can be written only when PLL is
disabled.
0: HSI oscillator clock / 2 selected as PLL input clock
1: Clock from PREDIV1 selected as PLL input clock
Note: When changing the main PLL’s entry clock source, the original clock source must be switched
off only after the selection of the new clock source.*/

	RCC_CFGR|= (0<<16);

	/*Bits 21:18 PLLMUL[3:0]: PLL multiplication factor

These bits are written by software to define the PLL multiplication factor. They can be written only
when PLL is disabled.
000x: Reserved
0010: PLL input clock x 4
0011: PLL input clock x 5
0100: PLL input clock x 6
0101: PLL input clock x 7
0110: PLL input clock x 8
0111: PLL input clock x 9
10xx: Reserved
1100: Reserved
1101: PLL input clock x 6.5
111x: Reserved
Caution: The PLL output frequency must not exceed 72 MHz.*/

RCC_CFGR|= ((0<<18)|(1<<19)|(1<<20)|(0<<21));


/*Bits 7:4 HPRE[3:0]: AHB prescaler
Set and cleared by software to control AHB clock division factor.
0xxx: SYSCLK not divided
1000: SYSCLK divided by 2
1001: SYSCLK divided by 4
1010: SYSCLK divided by 8
1011: SYSCLK divided by 16
1100: SYSCLK divided by 64
1101: SYSCLK divided by 128
1110: SYSCLK divided by 256
1111: SYSCLK divided by 512*/

//No division needed

	/*Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)

Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
0xx: HCLK not divided
100: HCLK divided by 2
101: HCLK divided by 4
110: HCLK divided by 8
111: HCLK divided by 16*/
RCC_CFGR|= ((1<<11)|(0<<12)|(1<<13));


/*Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
0xx: HCLK not divided
100: HCLK divided by 2
101: HCLK divided by 4
110: HCLK divided by 8
111: HCLK divided by 16*/

RCC_CFGR|= ((1<<8)|(0<<9)|(0<<10));


	/*Bit 24 PLLON: PLL enable
Set and cleared by software to enable PLL.
Cleared by hardware when entering Stop or Standby mode. This bit can not be reset if the
PLL clock is used as system clock or is selected to become the system clock. Software
must disable the USB OTG FS clock before clearing this bit.
0: PLL OFF
1: PLL ON*/

	RCC_CFGR|= (1<<24);
}
int main(void)
{

	clockINIT();
	//Enable APB2 CLK BUS for GPIOA
	RCC_APB2ENR |= (1<<2);

	//Init GPIOA
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
while(1)
	{
		GPIOA_ODR |= 1<<13 ;
		for (int i = 0; i < 5000; i++); // arbitrary delay
		GPIOA_ODR &= ~(1<<13) ;
		for (int i = 0; i < 5000; i++); // arbitrary delay
	}
}