/* Qamar Elgohary */
/* Mastering Embedded System Online Diploma Lesson 3 Unit 3 */
/* LAB 2 Part 2 */

#include "stdint.h"

#define STACK_Start_SP 0x20001000

extern int main(void);
extern void Reset_Handler(void);

void NMI_Handler(void)__attribute__((weak,alias("Default_Handler")));
void BusFault_Handler(void)__attribute__((weak,alias("Default_Handler")));
void HardFault_Handler(void)__attribute__((weak,alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak,alias("Default_Handler")));
void MM_Handler(void)__attribute__((weak,alias("Default_Handler")));

uint32_t vectors[] __attribute__((section(".vectors"))) = {
STACK_Start_SP,
(uint32_t) &Reset_Handler,
(uint32_t) &NMI_Handler,
(uint32_t) &HardFault_Handler,
(uint32_t) &MM_Handler,
(uint32_t) &BusFault_Handler,
(uint32_t) &UsageFault_Handler,
};

extern unsigned int _E_text;
extern unsigned int _E_DATA;
extern unsigned int _S_DATA;
extern unsigned int _S_bss;
extern unsigned int _E_bss;


void Default_Handler(void)
{
	Reset_Handler();
}
void Reset_Handler(void)
{
	// copy data section from flash to sram
	unsigned int DATA_size = (unsigned char*)&_E_DATA - (unsigned char*)&_S_DATA ;
	unsigned char* P_src = (unsigned char*)&_E_text ;
	unsigned char* P_dst = (unsigned char*)&_S_DATA ;
	for (int i=0 ; i < DATA_size ; i++) 
	{	
		*((unsigned char*)P_dst++) = *((unsigned char*)P_src++) ;
	}
	
	// init the .bss with zero
	unsigned int bss_size = (unsigned char*)&_E_bss - (unsigned char*)&_S_bss ;
	for (int i=0 ; i < bss_size ; i++) 
	{	
		*((unsigned char*)P_dst++) = (unsigned char)0 ;
	}
	
	//jump to main 
	main();
}