/* Qamar Elgohary */
/* Mastering Embedded System Online Diploma Lesson 3 Unit 3 */
/* LAB 2 */

#include "stdlib.h"
#include "stdint.h"

typedef volatile unsigned int vuint32_t;



/*#####################################################################################################*/

                                          /* REGISTERS */

/*#####################################################################################################*/
#define RCC_BASE (0x40021000)
#define GPIOA_BASE (0x40010800)
#define RCC_APB2ENR (*(vuint32_t *)(RCC_BASE + 0x18))
#define GPIOA_CRH (*(vuint32_t *)(GPIOA_BASE + 0x04))
#define GPIOA_ODR (*(vuint32_t *)(GPIOA_BASE + 0x0C))

/*#####################################################################################################*/

                                        /* BIT FIELDS */

/*#####################################################################################################*/
#define RCC_IOPAEN (1<<2)
#define GPIOA13 (1<<13)

extern void NMI_Handler (void)
{

}
extern void BusFault_Handler (void)
{

}


typedef union
{
	vuint32_t all_fields;
	struct
	{
		vuint32_t reserved:13 ;
		vuint32_t P_13:1 ;
	}Pin;
}R_ODR_t;

volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(GPIOA_BASE + 0x0C) ;

void* _sbrk (int incr)
{
	static unsigned char* heap_ptr =NULL;
	unsigned char* prev_heap_ptr =NULL;
	extern unsigned int _E_bss ; //symbol
	extern unsigned int heap_End; //symbol

	//first time initalized 
	if (heap_ptr == NULL)	
			heap_ptr = (unsigned char*)&_E_bss;
	prev_heap_ptr = heap_ptr ;

	//protect stack 
	if ((heap_ptr +incr) > (unsigned char*)&heap_End)
		return (void*) NULL ;

	// Booking inc size
	heap_ptr += incr ;

	return (void*) prev_heap_ptr ;
}

int main(void) 
{
	int* p= (int*)malloc (4) ;
	free (p);
	RCC_APB2ENR |= RCC_IOPAEN;

	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	
	while (1)
	{
		R_ODR->Pin.P_13= 1; //Output 1
		for (int i=0; i<5000; i++); // arbitrary delay
		
		R_ODR->Pin.P_13= 0;
		for (int i=0; i<5000; i++); // arbitrary delay
	}
}
