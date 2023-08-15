
/*
 * STM32F103x8_USART_driver.c
 *
 *
 *	Created on: 7/15/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */



#include "usart.h"


//-------------------------------------------------
// GENERIC VARIABLES
//-------------------------------------------------

UART_Config_t* Global_UART_Config = NULL;
UART_Config_t G_UART_Config;

//-------------------------------------------------
// GENERIC FUNCTIONS
//-------------------------------------------------



//-------------------------------------------------
// APIs
//-------------------------------------------------


/**************************************************************
 * @Fn			-MCAL_UART_INIT
 * @Breif		-Initializes the UART (asynch)
 * @Param [in]		-USARTx where x can be (1,2,3 depending on device used)
 * @Param [in]		-PinConfig pointer to UART_Config_t structure that contains the configuration information for the specified UART
 * @Retval 		-None
 * Note			-Support for now Asynch mode & CLOCK 8MHZ
 */

void MCAL_UART_INIT (USART_Typedef* USARTx, UART_Config_t* UART_Config)
{
	uint32_t pclk, BRR;
	G_UART_Config = *UART_Config;
	Global_UART_Config = &G_UART_Config;


	//EN the clk for given USART peripheral
	if (USARTx == USART1)
		RCC_USART1_CLK_EN();
	else if (USARTx == USART2)
		RCC_USART2_CLK_EN();
	else if (USARTx == USART3)
		RCC_USART3_CLK_EN();

	//En the USART module Bit 13 UE: USART enable

	USARTx->CR1 |= 1<<13;

	//EN USART TX and RX according to the USART_MODE config
	USARTx->CR1 |= UART_Config->USART_MODE;

	//Payload width
	USARTx->CR1 |= UART_Config->Payload_length;

	//configuration of parity ctrl bit fields
	USARTx->CR1 |= UART_Config->Parity;

	//configure the no. of stop bits
	USARTx->CR2 |= UART_Config->StopBits;

	//configuration of hw flowctrl
	USARTx->CR3 |= UART_Config->FlowCTRL;

	//configuration of BRR (BAUDRATE REG)
	//PCLK1 for USART 2, 3
	//PCLK2 for USART 1

	if (USARTx == USART1)
	{
		pclk = MCAL_RCC_GET_PCLK2_FREQ();
	}

	if (USARTx == USART1)
	{
		pclk = MCAL_RCC_GET_PCLK2_FREQ();
	}
	BRR = UART_BRR_REG(pclk, UART_Config->BaudRate);
	USARTx->BRR =BRR;

	//ENABLE/DISABLE
	//USART1 CR1
	if (UART_Config->IRQ_ENABLE != UART_IRQ_ENABLE_NONE)
	{
		USARTx->CR1 |= (UART_Config->IRQ_ENABLE);

		// EN NVIC for USARTx IRQ
		if (USARTx == USART1)
		{
			NVIC_IRQ37_USART1_ENABLE;
		}

		else if (USARTx == USART2)
		{

			NVIC_IRQ38_USART2_ENABLE;
		}

		else if (USARTx == USART3)
		{

			NVIC_IRQ39_USART3_ENABLE;
		}
	}
}



/**************************************************************
 * @Fn			-MCAL_UART_DeINIT
 * @Breif		-Deinitializes the UART (asynch)
 * @Param [in]		-USARTx where x can be (1,2,3 depending on device used)
 * @Retval 		-None
 * Note			-Reset model by RCC
 */


void MCAL_UART_DeINIT (USART_Typedef* USARTx)
{
	if (USARTx == USART1)
	{
 		RCC_USART1_RESET();
		NVIC_IRQ37_USART1_DISABLE;
	}

	else if (USARTx == USART2)
	{
		RCC_USART2_RESET();
		NVIC_IRQ38_USART2_DISABLE;
	}
	else if (USARTx == USART3)
	{
 		RCC_USART3_RESET();
		NVIC_IRQ39_USART3_DISABLE;
	}

}

/**************************************************************
 * @Fn			-MCAL_UART_GPIO_SET_PINS
 * @Breif		-Initializes GPIO pins
 * @Param [in]		-USARTx where x can be (1,2,3 depending on device used)
 * @Retval 		-None
 * Note			-Check pin alternative table
 */

void MCAL_UART_GPIO_SET_PINS(USART_Typedef* USARTx)
{
	GPIO_PIN_CONFIG_t PinCfg;
	if (USARTx == USART1)
	{
 		//PA9 TX
 		//PA10 RX
 		//PA11 CTS
 		//PA12 RTS

		PinCfg.GPIO_PIN_NO = GPIO_PIN9;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		PinCfg.GPIO_PIN_NO = GPIO_PIN10;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if((Global_UART_Config->FlowCTRL ==  UART_FLOWCTRL_CTS) |(Global_UART_Config->FlowCTRL ==  UART_FLOWCTRL_RTS_CTS ))
		{
			PinCfg.GPIO_PIN_NO = GPIO_PIN11;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}
		if((Global_UART_Config->FlowCTRL ==  UART_FLOWCTRL_RTS) |(Global_UART_Config->FlowCTRL ==  UART_FLOWCTRL_RTS_CTS ))
		{
			PinCfg.GPIO_PIN_NO = GPIO_PIN12;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}
	}

	else if (USARTx == USART2)
	{
		//PA2 TX
 		//PA3 RX
 		//PA0 CTS
 		//PA1 RTS

		PinCfg.GPIO_PIN_NO = GPIO_PIN2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		PinCfg.GPIO_PIN_NO = GPIO_PIN3;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		if((Global_UART_Config->FlowCTRL ==  UART_FLOWCTRL_CTS) |(Global_UART_Config->FlowCTRL ==  UART_FLOWCTRL_RTS_CTS ))
		{
			PinCfg.GPIO_PIN_NO = GPIO_PIN0;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}
		if((Global_UART_Config->FlowCTRL ==  UART_FLOWCTRL_RTS) |(Global_UART_Config->FlowCTRL ==  UART_FLOWCTRL_RTS_CTS ))
		{
			PinCfg.GPIO_PIN_NO = GPIO_PIN1;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}
	}
	else if (USARTx == USART3)
	{
 		//PB10 TX
 		//PB11 RX
 		//PB13 CTS
 		//PA14 RTS

		PinCfg.GPIO_PIN_NO = GPIO_PIN10;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		PinCfg.GPIO_PIN_NO = GPIO_PIN11;
		PinCfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		if((Global_UART_Config->FlowCTRL ==  UART_FLOWCTRL_CTS) |(Global_UART_Config->FlowCTRL ==  UART_FLOWCTRL_RTS_CTS ))
		{
			PinCfg.GPIO_PIN_NO = GPIO_PIN13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

		}
		if((Global_UART_Config->FlowCTRL ==  UART_FLOWCTRL_RTS) |(Global_UART_Config->FlowCTRL ==  UART_FLOWCTRL_RTS_CTS ))
		{
			PinCfg.GPIO_PIN_NO = GPIO_PIN14;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}
	}


}

/**************************************************************
 * @Fn			-MCAL_UART_SEND_DATA
 * @Breif		-Send Buffer on UART
 * @Param [in]		-USARTx where x can be (1,2,3 depending on device used)
 * @Param [in]		-pTX_Buffer buffer
 * @Param [in]		-ENUM to check if polling mechanism is enabled
 * @Retval 		-None
 * Note			-Should initialize UART first
			When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
			the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
			because it is replaced by the parity.
			When receiving with the parity enabled, the value read in the MSB bit is the received parity bit.
 */
void MCAL_UART_SEND_DATA (USART_Typedef* USARTx, uint16_t* pTX_Buffer, enum Polling_Mechanism PollingEn)
{
	//Wait until TXE flag is set
	if ( PollingEn == ENABLE)
		while( !(USARTx->SR & 1<< 7));

	if (Global_UART_Config->Payload_length == UART_PayloadLength_9B)
	{
		USARTx->DR = (*pTX_Buffer & (uint16_t) 0x01FF);
	}
	else
	{
		USARTx->DR = (*pTX_Buffer & (uint8_t) 0xFF);
	}



}


/**************************************************************
 * @Fn			-MCAL_UART_RECEIVE_DATA
 * @Breif		-Receive Buffer on UART
 * @Param [in]		-USARTx where x can be (1,2,3 depending on device used)
 * @Param [in]		-pTX_Buffer buffer
 * @Param [in]		-ENUM to check if polling mechanism is enabled
 * @Retval 		-None
 * Note			-Should initialize UART first
 */


void MCAL_UART_RECEIVE_DATA (USART_Typedef* USARTx, uint16_t* pTX_Buffer, enum Polling_Mechanism PollingEn)
{
	//Wait until RXNE flag is set
	if ( PollingEn == ENABLE)
		while( !(USARTx->SR & 1<< 5));

	if (Global_UART_Config->Payload_length == UART_PayloadLength_9B)
	{
		if (Global_UART_Config->Parity == UART_PARITY_NONE)
		{
			*((uint16_t *)pTX_Buffer) = USARTx->DR ;

		}
		else
		{
			// Parity is used, so 8bits will be of user data and 1 bits is parity
			 *((uint16_t *) pTX_Buffer) = (USARTx->DR & (uint8_t )0xFF);
		}
	}
	else
	{

		//this is 8 bits
		if (Global_UART_Config->Parity == UART_PARITY_NONE)
		{
			//No parity so all 8 bits are considred data
			 *((uint16_t*)pTX_Buffer) =  (USARTx->DR & (uint8_t) 0xFF);
		}
		else
		{
			// Parity is used, so 7bits will be of user data and 1 bits is parity
			 *((uint16_t*)pTX_Buffer) = (USARTx->DR & (uint8_t) 0x7F);
		}
	}
	}




/**************************************************************
 * @Fn			- MCAL_UART_WAIT_TC
 * @Breif		-Check for TC flag
 * @Param [in]		-USARTx where x can be (1,2,3 depending on device used)
 * @Retval 		-None
 * Note			-
 */

void MCAL_UART_WAIT_TC (USART_Typedef* USARTx)
{
	while( !(USARTx->SR & 1<< 6));
}

//ISR
void USART1_IRQHandler (void)
{
	Global_UART_Config->P_IRQ_CALLBACK();
}

void USART2_IRQHandler (void)
{
	Global_UART_Config->P_IRQ_CALLBACK();

}
void USART3_IRQHandler (void)
{
	Global_UART_Config->P_IRQ_CALLBACK();

}
