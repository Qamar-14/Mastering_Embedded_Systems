/*
 *
 * STM32F103x8_gpio_driver.c
 *
 *
 *	Created on: 7/6/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */

//-------------------------------------------------
// INCLUDES
//-------------------------------------------------

#include "gpio.h"


uint8_t GET_CRLH_POSITION(uint16_t PIN_NUMBER)
{
	switch (PIN_NUMBER)
	{
		case GPIO_PIN0:
		return 0;
		break;

		case GPIO_PIN1:
		return 4;
		break;

		case GPIO_PIN2:
		return 8;
		break;

		case GPIO_PIN3:
		return 12;
		break;

		case GPIO_PIN4:
		return 16;
		break;

		case GPIO_PIN5:
		return 20;
		break;

		case GPIO_PIN6:
		return 24;
		break;

		case GPIO_PIN7:
		return 28;
		break;

		case GPIO_PIN8:
		return 0;
		break;

		case GPIO_PIN9:
		return 4;
		break;

		case GPIO_PIN10:
		return 8;
		break;

		case GPIO_PIN11:
		return 12;
		break;

		case GPIO_PIN12:
		return 16;
		break;

		case GPIO_PIN13:
		return 20;
		break;

		case GPIO_PIN14:
		return 24;
		break;

		case GPIO_PIN15:
		return 28;
		break;
	}
	return 0;

}

/**************************************************************
 * @Fn			-MCAL_GPIO_Init
 * @Breif		-Initializes the GPIOx PINy according to the specified parameter in the pin config
 * @Param [in]		-GPIOx where x can be (A..E depending on device used) to select the GPIO peripheral
 * @Param [in]		-PinConfig pointer to a GPIO_PIN_CONFIG_t structure that contains the configuration information for the specified GPIO PIN
 * @Retval 		-None
 * Note			-STM32F103x8 MCU has GPIO A,B,C,D,E Modules
			 But LQFP48 has only GPIO A,B, Part of C,D exported as external pins from the MCU
 */

void MCAL_GPIO_Init	(GPIO_Typedef *GPIOx , GPIO_PIN_CONFIG_t* PINconfig)
{
	//Port configuration register low (GPIOx_CRL) (x=A..G) configures pins from 0 to 7
	//Port configuration register high (GPIOx_CRH) (x=A..G) configures pins from 8 to 15
	volatile uint32_t* configReg = NULL;
	uint8_t PIN_config =0;

	configReg = (PINconfig->GPIO_PIN_NO > GPIO_PIN7) ? &GPIOx->CRH : &GPIOx->CRL;

	(*configReg) &= ~(0xF << GET_CRLH_POSITION(PINconfig->GPIO_PIN_NO ));


	//If pin is output

	if( (PINconfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP) || (PINconfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD) || (PINconfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP))
 	{
		PIN_config= ( (( (PINconfig->GPIO_MODE -4) <<2 ) | (PINconfig->GPIO_OUTPUT_SPEED)) & 0x0F);
	}

	//Pin is input
	else //Mode = 00: Input mode (reset state)
	{
		if ( (PINconfig->GPIO_MODE == GPIO_MODE_INPUT_FLOATING) || (PINconfig->GPIO_MODE == GPIO_MODE_AF_INPUT))
		{
			//Set CNF8[1:0] MODE8[1:0] 00
			PIN_config = (( ( (PINconfig->GPIO_MODE) <<2 ) | 0x0) & 0x0F);
		}
		/*else if (PINconfig->GPIO_MODE == GPIO_MODE_AF_INPUT) //Consider it as input floating
		{
			PIN_config = (( (GPIO_MODE_INPUT_FLOATING <<2 ) | 0x0) & 0x0F);

		}*/

		else
		{
			PIN_config = (( (GPIO_MODE_INPUT_PU <<2 ) | 0x0) & 0x0F);
			if (PINconfig->GPIO_MODE == GPIO_MODE_INPUT_PU )
			{
				//PxODR = 1 INPUT pull-up :Table 20. Port bit configuration table
				GPIOx->ODR |= (PINconfig->GPIO_PIN_NO);
			}
			else
			{
				//PxODR = 0 INPUT pull-down Table 20. Port bit configuration table
				GPIOx->ODR &= ~ (PINconfig->GPIO_PIN_NO);
			}

		}
	}
	(*configReg) |= ( (PIN_config) << GET_CRLH_POSITION(PINconfig->GPIO_PIN_NO ));

}

/**************************************************************
 * @Fn			-MCAL_GPIO_DeInit
 * @Breif		-Resets all the GPIO registers
 * @Param [in]		-GPIOx where x can be (A..E depending on device used) to select the GPIO peripheral
 * @Retval 		-None
 * Note			-None
 */
void MCAL_GPIO_DeInit	(GPIO_Typedef *GPIOx)
{
	/* GPIOx->BRR = 0x00000000;
	GPIOx->BSRR =0x00000000;
	GPIOx->CRH = 0x44444444;
	GPIOx->CRL = 0x44444444;
	//GPIOx->IDR = ;(READ ONLY)
	GPIOx->LCKR = 0x00000000;
	GPIOx->ODR = 0x00000000;
	*/

	//APB2 peripheral reset regs (reset controller) RCC_APB2RSTR
	//Set & Cleared by sw

	if (GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}

	if (GPIOx == GPIOB)
	{
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}
	if (GPIOx == GPIOC)
	{
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}
	if (GPIOx == GPIOD)
	{
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}
	if (GPIOx == GPIOE)
	{
		RCC->APB2RSTR |= (1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}

}

/**************************************************************
 * @Fn			-MCAL_GPIO_READ_PIN
 * @Breif		-Reads specific PIN
 * @Param [in]		-GPIOx where x can be (A..E depending on device used) to select the GPIO peripheral
 * @Param [in]		-PIN NO. (Set pins according to PIN_NO_DEFINE @ref)
 * @Retval 		-Input pin value according to Pin state (@ref GPIO_PIN_STATE)
 * Note			-None
 */
uint8_t MCAL_GPIO_READ_PIN 	(GPIO_Typedef *GPIOx , uint16_t PIN)
{
	uint8_t bitstatus;
	if ( ( (GPIOx->IDR ) & PIN ) != (uint32_t)GPIO_PIN_RESET)
	{
		bitstatus = GPIO_PIN_SET;
	}
	else
	{
		bitstatus = GPIO_PIN_RESET;
	}

	return 	bitstatus;

}

/**************************************************************
 * @Fn			-MCAL_GPIO_READ_PORT
 * @Breif		-Reads specific port
 * @Param [in]		-GPIOx where x can be (A..E depending on device used) to select the GPIO peripheral
 * @Retval 		-Input port value
 * Note			-None
 */
uint16_t MCAL_GPIO_READ_PORT	(GPIO_Typedef *GPIOx)
{
	uint16_t Port_Value;
	Port_Value = (uint16_t)GPIOx->IDR;
	return Port_Value;
}

/**************************************************************
 * @Fn			-MCAL_GPIO_WRITE_PORT
 * @Breif		-Writes on specific input port
 * @Param [in]		-GPIOx where x can be (A..E depending on device used) to select the GPIO peripheral
 * @Param [in]		-Port Value
 * @Retval 		-None
 * Note			-None
 */


void MCAL_GPIO_WRITE_PORT(GPIO_Typedef *GPIOx, uint8_t value)
{
	GPIOx->ODR = ( uint32_t )value;
}

/**************************************************************
 * @Fn			-MCAL_GPIO_WRITE_PIN
 * @Breif		-Writes on specific input PIN
 * @Param [in]		-GPIOx where x can be (A..E depending on device used) to select the GPIO peripheral
 * @Param [in]		-PIN NO. (Set pins according to PIN_NO_DEFINE @ref)
 * @Param [in]		-PIN Value
 * @Retval 		-None
 * Note			-None
 */
void MCAL_GPIO_WRITE_PIN 	(GPIO_Typedef *GPIOx, uint16_t PIN , uint8_t value)
{
	if (value != (uint32_t)GPIO_PIN_RESET)
	{
		//GPIOx->ODR |= PIN ;

		//Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		//These bits are write-only and can be accessed in Word mode only.
		//0: No action on the corresponding ODRx bit
		//1: Set the corresponding ODRx bit
		  GPIOx->BSRR = (uint32_t)PIN ;

	}

	else
	{
		//Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
		//These bits are write-only and can be accessed in Word mode only.
		//0: No action on the corresponding ODRx bit
		//1: Reset the corresponding ODRx bit
		  GPIOx->BRR = PIN ;
	}
}

/**************************************************************
 * @Fn			-MCAL_GPIO_TOGGLE_PIN
 * @Breif		-Toggles specific pin
 * @Param [in]		-GPIOx where x can be (A..E depending on device used) to select the GPIO peripheral
 * @Param [in]		-PIN NO. (Set pins according to PIN_NO_DEFINE @ref)
 * @Retval 		-None
 * Note			-None
 */

void MCAL_GPIO_TOGGLE_PIN 	(GPIO_Typedef *GPIOx , uint16_t PIN)
{
	GPIOx->ODR ^= (uint32_t )PIN;
}

/**************************************************************
 * @Fn			-MCAL_GPIO_Lock_PIN
 * @Breif		-Locks specific pin (The locking mechanism allows the IO configuration to be frozen
 * @Param [in]		-GPIOx where x can be (A..E depending on device used) to select the GPIO peripheral
 * @Param [in]		-PIN NO. (Set pins according to PIN_NO_DEFINE @ref)
 * @Retval 		-OK if pin config is locked or ERROR if pin not locked (@ref GPIO_RETURN_LOCK)
 * Note			-This register is used to lock the configuration of the port bits when a correct write sequence
		       	is applied to bit 16 (LCKK). The value of bits [15:0] is used to lock the configuration of the
			GPIO. During the write sequence, the value of LCKR[15:0] must not change. When the
			LOCK sequence has been applied on a port bit it is no longer possible to modify the value of
			the port bit until the next reset.
 */

uint8_t MCAL_GPIO_LOCK_PIN 	(GPIO_Typedef *GPIOx , uint16_t PIN)
{
	//Bit 16 LCKK[16]: Lock key
	//This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	//0: Port configuration lock key not active
	//1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	//LOCK key writing sequence:
	//Write 1
	//Write 0
	//Write 1
	//Read 0
	//Read 1 (this read is optional but confirms that the lock is active)
	//Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	//Any error in the lock sequence will abort the lock.

	//Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	//These bits are read write but can only be written when the LCKK bit is 0.
	//0: Port configuration not locked
	//1: Port configuration locked.

	//set LCKK[16]

	volatile uint32_t temp = 1<<16;
	//set the LCKy
	temp |= PIN;

	//Write 1
	GPIOx->LCKR = temp;
	//Write 0
	GPIOx->LCKR = PIN;
	//Write 1
	GPIOx->LCKR = temp;

	//Read 0
	temp = GPIOx->LCKR;

	//Read 1
	if ((uint32_t) (GPIOx->LCKR & 1<<16))
	{
		return (GPIO_RETURN_LOCK_EN);

	}
	else
	{
		return (GPIO_RETURN_LOCK_ERROR);

	}

}


void MCAL_GPIO_SET_PIN_OUTPUT(GPIO_Typedef *GPIOx, uint16_t PIN, uint8_t MODE, uint8_t SPEED)
{
	GPIO_PIN_CONFIG_t PinConfig;
    PinConfig.GPIO_PIN_NO = PIN;
    PinConfig.GPIO_MODE = MODE;
    PinConfig.GPIO_OUTPUT_SPEED = SPEED;
    MCAL_GPIO_Init(GPIOx, &PinConfig);
}
void MCAL_GPIO_SET_PIN_INPUT(GPIO_Typedef *GPIOx, uint16_t PIN, uint8_t MODE)
{
	GPIO_PIN_CONFIG_t PinConfig;
    PinConfig.GPIO_PIN_NO = PIN;
    PinConfig.GPIO_MODE = MODE;
    MCAL_GPIO_Init(GPIOx, &PinConfig);
}
