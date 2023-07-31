/*
 *
 * STM32F103x8_EXTI_driver.c
 *
 *
 *	Created on: 7/26/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */


//-------------------------------------------------
// INCLUDES
//-------------------------------------------------

#include "../../../../../stm32/Src/STM32F103C_Drivers/MCAL_Drivers/EXTI_DRIVER/ext_interrupt.h"

//-------------------------------------------------
// Generic Variables
//-------------------------------------------------

void (* GP_IRQ_CALLBACK[15])(void);

//-------------------------------------------------
// Generic Macros
//-------------------------------------------------

 #define AFIO_GPIO_EXTI_Mapping(x)	( (x==GPIOA)?0:(x == GPIOB)?1:(x==GPIOC)?2:(x==GPIOD)?3:0 )

//-------------------------------------------------
// Generic Functions
//-------------------------------------------------

void Enable_NVIC (uint16_t IRQ)
{
	switch(IRQ)
	{
		case 0:
			NVIC_IRQ6_EXTI0_ENABLE;
			break;
		case 1:
			NVIC_IRQ7_EXTI1_ENABLE;
			break;
		case 2:
			NVIC_IRQ8_EXTI2_ENABLE;
			break;
		case 3:
			NVIC_IRQ9_EXTI3_ENABLE;
			break;
		case 4:
			NVIC_IRQ10_EXTI4_ENABLE;
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			NVIC_IRQ23_EXTI5_9_ENABLE;
			break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			NVIC_IRQ40_EXTI10_15_ENABLE;
			break;

	}

}
void Disable_NVIC (uint16_t IRQ)
{
	switch(IRQ)
	{
		case 0:
			NVIC_IRQ6_EXTI0_DISABLE;
			break;
		case 1:
			NVIC_IRQ7_EXTI1_DISABLE;
			break;
		case 2:
			NVIC_IRQ8_EXTI2_DISABLE;
			break;
		case 3:
			NVIC_IRQ9_EXTI3_DISABLE;
			break;
		case 4:
			NVIC_IRQ10_EXTI4_DISABLE;
			break;
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			NVIC_IRQ23_EXTI5_9_DISABLE;
			break;
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			NVIC_IRQ23_EXTI5_9_DISABLE;
			break;

	}

}

void UPDATE_EXTI(EXTI_PIN_CONFIG_t* EXTI_Config)
{
	//1- Configure GPIO to be AF Input -> Floating input
	MCAL_GPIO_SET_PIN_INPUT(EXTI_Config->EXTI_PIN.GPIO_PORT, EXTI_Config->EXTI_PIN.PIN, GPIO_MODE_INPUT_FLOATING);

	//2-Update AFIO to route between EXTI line with port A,B,C,D
	uint8_t AFIO_EXTICR_Index;
	uint8_t AFIO_EXTICR_Position;

	AFIO_EXTICR_Index = (EXTI_Config->EXTI_PIN.EXTI_InputLineNumber)/4;
	AFIO_EXTICR_Position = ((EXTI_Config->EXTI_PIN.EXTI_InputLineNumber) %4)*4;

	AFIO->EXTICR[AFIO_EXTICR_Index] |= (( AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_PORT) & 0xF) << AFIO_EXTICR_Position);

	//3- Update Rising or Falling reg or both

	EXTI->RTSR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
	EXTI->FTSR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	switch(EXTI_Config->TRIGGER_CASE )
		{
		case EXTI_TRIGGER_RISING :
			EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			break;
		case EXTI_TRIGGER_FALLING :
			EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			break;
		case EXTI_TRIGGER_RISING_FALLING:
			EXTI->RTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			EXTI->FTSR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
			break;
		}


	//4- Update IRQ handling callback
	GP_IRQ_CALLBACK[EXTI_Config->EXTI_PIN.EXTI_InputLineNumber] = EXTI_Config->P_IRQ_CALLBACK;

	//5-ENABLE/DISABLE IRQ
	if (EXTI_Config->IRQ_EN == EXTI_IRQ_ENABLE)
	{
		EXTI->IMR |= (1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		Enable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	}
	else if (EXTI_Config->IRQ_EN == (uint8_t)EXTI_IRQ_DISABLE)
	{
		EXTI->IMR &= ~(1 << EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);
		Disable_NVIC(EXTI_Config->EXTI_PIN.EXTI_InputLineNumber);

	}
	else{
	//Do nothing
	}
}




//-------------------------------------------------
// APIs Functions Definitions
//-------------------------------------------------

/**************************************************************
 * @Fn			-MCAL_EXTI_DEinit
 * @Breif		-Reset EXTI regs and NVIC corresponding IRQ mask
 * @Retval 		-None
 * Note			-None
 */

void MCAL_EXTI_DeInit	(void)
{
	EXTI->IMR = 0x00000000;
	EXTI->EMR = 0x00000000;
	EXTI->RTSR = 0x00000000;
	EXTI->FTSR = 0x00000000;
	EXTI->SWIER = 0x00000000;

	EXTI->PR = 0xFFFFFFFF;

	// Disable EXTI IRQ from NVIC
	NVIC_IRQ6_EXTI0_DISABLE;
 	NVIC_IRQ7_EXTI1_DISABLE;
 	NVIC_IRQ8_EXTI2_DISABLE;
	NVIC_IRQ9_EXTI3_DISABLE;
 	NVIC_IRQ10_EXTI4_DISABLE;
 	NVIC_IRQ23_EXTI5_9_DISABLE;
	NVIC_IRQ40_EXTI10_15_DISABLE;
}


/**************************************************************
 * @Fn			-MCAL_EXTI_GPIO_Init
 * @Breif		-This is used to initialize EXTI from specific GPIO PIN and specify the mask, trigger condition and IRQ callback
 * @Param [in]		-EXTI_Config set by @ref EXTI_DEFINE, EXT_TRIGGER_DEFINE, EXT_IRQ_DEFINE
 * @Retval 		-None
 * Note			-None
 */

void MCAL_EXTI_Init (EXTI_PIN_CONFIG_t* EXTI_Config)
{
	UPDATE_EXTI(EXTI_Config);
}

/**************************************************************
 * @Fn			-MCAL_EXTI_GPIO_Update
 * @Breif		-This is used to initialize EXTI from specific GPIO PIN and specify the mask, trigger condition and IRQ callback
 * @Param [in]		-EXTI_Config set by @ref EXTI_DEFINE, EXT_TRIGGER_DEFINE, EXT_IRQ_DEFINE
 * @Retval 		-None
 * Note			-None
 */

void MCAL_EXTI_GPIO_Update(EXTI_PIN_CONFIG_t* EXTI_Config)
{
	UPDATE_EXTI(EXTI_Config);

}

void MCAL_EXTI_SET(EXTI_GPIO_MAPPING_t EXTI_PIN, uint8_t EXTI_TRIGGER ,uint8_t EXTI_IRQ ,void(*P_IRQ_FUNCTION)(void) )
{
	EXTI_PIN_CONFIG_t EXTI_PinConfig;
	EXTI_PinConfig.EXTI_PIN = EXTI_PIN;
	EXTI_PinConfig.IRQ_EN = EXTI_IRQ;
	EXTI_PinConfig.TRIGGER_CASE = EXTI_TRIGGER;
	EXTI_PinConfig.P_IRQ_CALLBACK=P_IRQ_FUNCTION;
	MCAL_EXTI_Init(&EXTI_PinConfig);

}
//-------------------------------------------------
// ISR
//-------------------------------------------------

//PRx: Pending bit
//0: No trigger request occurred
//1: selected trigger request occurred
//This bit is set when the selected edge event arrives on the external interrupt line. This bit is cleared by writing a ‘1’ into the bit.

void EXTI0_IRQHandler(void)
{
	EXTI->PR |= 1<<0;
	///Call IRQ_CALLBACK
	GP_IRQ_CALLBACK[0]();
}
void EXTI1_IRQHandler(void)
{
	EXTI->PR |= 1<<1;
	///Call IRQ_CALLBACK
	GP_IRQ_CALLBACK[1]();
}
void EXTI2_IRQHandler(void)
{
	EXTI->PR |= 1<<2;
	///Call IRQ_CALLBACK
	GP_IRQ_CALLBACK[2]();
}
void EXTI3_IRQHandler(void)
{
	EXTI->PR |= 1<<3;
	///Call IRQ_CALLBACK
	GP_IRQ_CALLBACK[3]();
}
void EXTI4_IRQHandler(void)
{
	EXTI->PR |= 1<<4;
	///Call IRQ_CALLBACK
	GP_IRQ_CALLBACK[4]();
}
void EXTI5_9_IRQHandler(void)
{
	if(EXTI->PR & 1<<5)
	{
		EXTI->PR |= 1<<5;
		GP_IRQ_CALLBACK[5]();
	}
	if(EXTI->PR & 1<<6)
	{
		EXTI->PR |= 1<<6;
		GP_IRQ_CALLBACK[6]();
	}
	if(EXTI->PR & 1<<7)
	{
		EXTI->PR |= 1<<7;
		GP_IRQ_CALLBACK[7]();
	}
	if(EXTI->PR & 1<<8)
	{
		EXTI->PR |= 1<<8;
		GP_IRQ_CALLBACK[8]();
	}
	if(EXTI->PR & 1<<9)
	{
		EXTI->PR |= 1<<9;
		GP_IRQ_CALLBACK[9]();
	}
}
void EXTI10_15_IRQHandler(void)
{
	if(EXTI->PR & 1<<10)
	{
		EXTI->PR |= 1<<10;
		GP_IRQ_CALLBACK[10]();
	}
	if(EXTI->PR & 1<<11)
	{
		EXTI->PR |= 1<<11;
		GP_IRQ_CALLBACK[11]();
	}
	if(EXTI->PR & 1<<12)
	{
		EXTI->PR |= 1<<12;
		GP_IRQ_CALLBACK[12]();
	}
	if(EXTI->PR & 1<<13)
	{
		EXTI->PR |= 1<<13;
		GP_IRQ_CALLBACK[13]();
	}
	if(EXTI->PR & 1<<14)
	{
		EXTI->PR |= 1<<14;
		GP_IRQ_CALLBACK[14]();
	}
	if(EXTI->PR & 1<<15)
	{
		EXTI->PR |= 1<<15;
		GP_IRQ_CALLBACK[15]();
	}
}
