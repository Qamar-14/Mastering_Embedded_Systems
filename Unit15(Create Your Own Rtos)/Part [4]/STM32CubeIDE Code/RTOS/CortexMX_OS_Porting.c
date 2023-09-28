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
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;

}

void Start_Ticker()
{
	//Initialize clock tree (RCC-> Systick timer & CPU ) 8MHz
	//8 Mhz
	//1 count = 0.125 us
	//x count = 1 ms
	//x = 8000 count
	SysTick_Config(8000);
}

unsigned char SysTick_led ;

void SysTick_Handler()
{
	SysTick_led ^=1 ;

	//Update waiting Time
	Update_WaitingTime();

	//Determine pCurrent and pNext
	OS_Decision();

	//Switch Context and Restore
	trigger_OS_PendSV();

}
