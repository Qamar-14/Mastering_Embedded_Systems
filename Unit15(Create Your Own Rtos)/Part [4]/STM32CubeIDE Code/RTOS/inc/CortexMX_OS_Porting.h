/*
 * CortexMX_OS_Porting.h
 *
 *	Created on: 9/22/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 *
 */


#ifndef INC_CORTEXMX_PORTING_H_
#define INC_CORTEXMX_PORTING_H_

//-------------------------------------------------
// INCLUDES
//-------------------------------------------------
#include "core_cm3.h"

extern int _estack;
extern int _eheap;

//-------------------------------------------------
// MACROS
//-------------------------------------------------
#define MainStackSize 4096

#define OS_SWITCH_SP_TO_PSP		__asm volatile(" mrs r0, CONTROL \n\t mov r1, #0x02 \n\t orr r0, r0, r1 \n\t msr CONTROL, r0 \n\t")
#define OS_SWITCH_SP_TO_MSP		__asm volatile(" mrs r0, CONTROL \n\t mov r1, #0x05 \n\t and r0, r0, r1 \n\t msr CONTROL, r0 \n\t")


#define OS_SET_PSP(add)			__asm volatile(" mov r0, %0 \n\t msr PSP, r0 \n\t" : : "r" (add))
#define OS_SET_MSP(add)			__asm volatile(" mov r0, %0 \n\t msr MSP, r0 \n\t" : : "r" (add))

#define OS_GET_PSP(add)			__asm volatile(" mrs r0, PSP \n\t mov %0, r0 \n\t" : "=r" (add))
#define OS_GET_MSP(add)			__asm volatile(" mrs r0, MSP \n\t mov %0, r0 \n\t" : "=r" (add))



#define OS_SWITCH_TO_PRIVILEGED					__asm("mrs r3, CONTROL \n\t" \
												"lsr r3, r3, #0x1 \n\t" \
												"lsl r3, r3, #0x1 \n\t" \
												"msr CONTROL,r3")

#define OS_SWITCH_TO_UNPRIVILEGED				__asm("mrs r3, CONTROL \n\t" \
												"orr r3, r3, #0x1 \n\t" \
												"msr CONTROL,r3")



//-------------------------------------------------
// APIs
//-------------------------------------------------
void trigger_OS_PendSV();
void Start_Ticker();
void HW_init();

#endif /* INC_CORTEXMX_PORTING_H_*/
