/*
 *
 * STM32F103x8_USART_driver.h
 *
 *
 *	Created on: 7/15/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */
#ifndef INC_STM32F103x8_USART_DRIVER_H_
#define INC_STM32F103x8_USART_DRIVER_H_

//-------------------------------------------------
// INCLUDES
//-------------------------------------------------

#include <STM32F103.h>
#include "GPIO_DRIVER/gpio.h"
#include "RCC_DRIVER/rcc.h"

//-------------------------------------------------
// USART CONFIGURATION STRUCTURES
//-------------------------------------------------

typedef struct
{
	uint8_t		USART_MODE;	// Specifies TX/RX Enable/Disable
					// This parameter must be set by @ref UART_MODE_DEFINE

	uint32_t	BaudRate;	// Configures the UART communication BaudRate
					// This parameter must be set by @ref UART_BaudRate_DEFINE

	uint8_t		Payload_length;	// Specifies the number of data bits transmitted or received in a frame.
					// This parameter must be set by @ref UART_PayloadLength_DEFINE

	uint8_t		Parity;		// Specifies parity mode
					// This parameter must be set by @ref UART_PARITY_DEFINE

	uint8_t		StopBits;	// Specifies the number of stop bits transmitted
					// This parameter must be set by @ref UART_StopBits_DEFINE

	uint8_t		FlowCTRL;	// Specifies wether hardware flow ctrl mode is enabled or disabled
					// This parameter must be set by @ref UART_FLOWCTRL_DEFINE

	uint8_t		IRQ_ENABLE;	// ENABLE/DISABLE UART IRQ TX/RX
					// This parameter must be set by @ref UART_IRQ_EN_DEFINE

	void (* P_IRQ_CALLBACK)(void);		// Set the c function which will be called once the IRQ occurs

}UART_Config_t;

//-------------------------------------------------
// MACROS
//-------------------------------------------------

//@ref UART_MODE_DEFINE
#define UART_MODE_RX		(uint32_t)(1<<2)	//Bit 2 in USART_CR1 RE: Transmitter enable
#define UART_MODE_TX		(uint32_t)(1<<3)	//Bit 3 in USART_CR1 TE: Transmitter enable
#define UART_MODE_RX_TX		((uint32_t)(1<<2 | 1<<3))


//@ref UART_BaudRate_DEFINE
#define UART_BaudRate_2400		2400
#define UART_BaudRate_9600		9600
#define UART_BaudRate_19200		19200
#define UART_BaudRate_57600		57600
#define UART_BaudRate_115200		115200
#define UART_BaudRate_230400		230400
#define UART_BaudRate_460800		460800
#define UART_BaudRate_921600		921600
#define UART_BaudRate_2250000		2250000
#define UART_BaudRate_4500000		4500000


// @ref UART_PayloadLength_DEFINE
#define UART_PayloadLength_8B		(uint32_t)(0)
#define UART_PayloadLength_9B		(uint32_t)(1<<12)


//@ref UART_PARITY_DEFINE
#define UART_PARITY_NONE		(uint32_t)(0)
#define UART_PARITY_EVEN		(uint32_t)(1<<10)
#define UART_PARITY_ODD	 		(uint32_t)(1<<10 | 1<<9)


//@ref UART_StopBits_DEFINE
/*Bits 13:12 STOP: STOP bits
These bits are used for programming the stop bits.
00: 1 Stop bit
01: 0.5 Stop bit
10: 2 Stop bits
11: 1.5 Stop bit
The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5.*/
#define  UART_StopBit_1		 	(uint32_t)(0)
#define  UART_StopBit_1_half		(uint32_t)(3<<12)
#define  UART_StopBit_2		 	(uint32_t)(2<<12)
#define  UART_StopBit_half		(uint32_t)(1<<12)

// @ref UART_FLOWCTRL_DEFINE
/*Bit 9 CTSE: CTS enable
0: CTS hardware flow control disabled
1: CTS mode enabled, data is only transmitted when the CTS input is asserted (tied to 0). If
the CTS input is deasserted while a data is being transmitted, then the transmission is
completed before stopping. If a data is written into the data register while CTS is deasserted,
the transmission is postponed until CTS is asserted.
This bit is not available for UART4 & UART5.
Bit 8 RTSE: RTS enable
0: RTS hardware flow control disabled
1: RTS interrupt enabled, data is only requested when there is space in the receive buffer.
The transmission of data is expected to cease after the current character has been
transmitted. The RTS output is asserted (tied to 0) when a data can be received.
This bit is not available for UART4 & UART5.*/

#define  UART_FLOWCTRL_NONE		(uint32_t)(0)
#define  UART_FLOWCTRL_RTS		(uint32_t)(1<<8)
#define  UART_FLOWCTRL_CTS	 	(uint32_t)(1<<9)
#define  UART_FLOWCTRL_RTS_CTS		(uint32_t)(1<<8 | 1<<9)


// @ref UART_IRQ_EN_DEFINE
#define  UART_IRQ_ENABLE_NONE		(uint32_t)(0)
#define  UART_IRQ_ENABLE_TXE		(uint32_t)(1<<7)
#define  UART_IRQ_ENABLE_TC			(uint32_t)(1<<6)
#define  UART_IRQ_ENABLE_RXNEIE		(uint32_t)(1<<5)
#define  UART_IRQ_ENABLE_PE			(uint32_t)(1<<8)


enum Polling_Mechanism {
	ENABLE,
	DISABLE
};

//BAUDRATE Calculations
//USARTDIV= fclk /(16* baudrate)
//USARTDIV_MUL100 = (uint32_t)((100*fclk)/(16*baudrate)) == 25*fclk/4*baudrate
//Mantissa_MUL100 = USARTDIV*100 //Integer part *100
//DIV_Mantissa= USARTDIV (Integer part)
//DIV_Fraction= ((SARTDIV_MUL100 - Mantissa_MUL100)*16)/100

#define  USARTDIV(_PCLK_,_BAUD_)				(uint32_t)(_PCLK_/(16*_BAUD_))
#define  USARTDIV_MUL100(_PCLK_,_BAUD_) 		(uint32_t)((25*_PCLK_)/(4*_BAUD_))
#define  Mantissa_MUL100(_PCLK_,_BAUD_)			(uint32_t)(USARTDIV(_PCLK_,_BAUD_)*100)
#define  DIV_Mantissa(_PCLK_,_BAUD_)			(uint32_t)(USARTDIV(_PCLK_,_BAUD_))
#define  DIV_Fraction(_PCLK_,_BAUD_)			(uint32_t)(((USARTDIV_MUL100(_PCLK_,_BAUD_) -Mantissa_MUL100(_PCLK_,_BAUD_))*16)/100)
#define  UART_BRR_REG(_PCLK_,_BAUD_)			((DIV_Mantissa(_PCLK_,_BAUD_) << 4) | (DIV_Fraction(_PCLK_,_BAUD_) & 0xF))





//-------------------------------------------------
// APIs supported by "MCAL USART DRIVER"
//-------------------------------------------------

void MCAL_UART_INIT (USART_Typedef* USARTx, UART_Config_t* UART_Config);
void MCAL_UART_DeINIT (USART_Typedef* USARTx);

void MCAL_UART_GPIO_SET_PINS(USART_Typedef* USARTx);

void MCAL_UART_SEND_DATA (USART_Typedef* USARTx, uint16_t* pTX_Buffer, enum Polling_Mechanism PollingEn);
void MCAL_UART_RECEIVE_DATA (USART_Typedef* USARTx, uint16_t* pTX_Buffer, enum Polling_Mechanism PollingEn);

void MCAL_UART_WAIT_TC (USART_Typedef* USARTx);

//TODO usart_Init, usart_DMA_init ...


#endif
