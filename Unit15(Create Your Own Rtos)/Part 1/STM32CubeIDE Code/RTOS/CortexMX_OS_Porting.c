/*
 *
 * CortexMX_OS_Porting.c
 *
 *
 *	Created on: 9/22/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */



//-------------------------------------------------
// INCLUDES
//-------------------------------------------------

#include "CortexMX_OS_Porting.h"


void BusFault_Handler()
{
	while(1);
}
void HardFault_Handler()
{
	while(1);

}
void UsageFault_Handler()
{
	while(1);
}
void MemManage_Handler()
{
	while(1);
}


__attribute ((naked)) void SVC_Handler ()
{
	__asm ("tst lr, #4 \n\t"
			"ITE EQ \n\t" // To execute Thumb instructions conditionally, you can either use an IT instruction, or a conditional branch instruction.
			"mrseq r0,MSP \n\t "
			"mrsne r0,PSP \n\t"
			"B OS_SVC");
}
void SysTick_Handler()
{

}

void HW_init()
{
	//Initialize clock tree (RCC-> Systick timer & CPU ) 8MHz
	//8 Mhz
	//1 count = 0.125 us
	//x count = 1 ms
	//x = 8000 count

	//	decrease PenSV  interrupt priority to be  smaller than or equal  SySTICK Timer
	//SysTICK have a priority 14
	__NVIC_SetPriority(PendSV_IRQn, 15) ;

}
void trigger_OS_PendSV()
{

}

void Start_Ticker()
{

}
