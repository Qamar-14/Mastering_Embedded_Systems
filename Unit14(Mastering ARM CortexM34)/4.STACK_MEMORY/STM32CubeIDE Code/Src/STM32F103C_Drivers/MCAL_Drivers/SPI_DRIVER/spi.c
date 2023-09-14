
 /*
 * STM32F103x8_SPI_driver.c
 *
 *
 *	Created on:
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */


#include "spi.h"


//-------------------------------------------------
// GENERIC VARIABLES
//-------------------------------------------------

SPI_Config_t* Global_SPI_Config[2] ={NULL,NULL};

//-------------------------------------------------
// GENERIC FUNCTIONS
//-------------------------------------------------

#define	SPI1_INDEX	0
#define	SPI2_INDEX	1

#define   SPI_SR_RXNE            ((uint8_t)0x01)         //Bit 0 RXNE: Receive buffer not empty
#define   SPI_SR_TXE             ((uint8_t)0x02)         //Bit 1 TXE: Transmit buffer empty


//#define SPI_SR_TXE               1<<1
//#define SPI_SR_RXNE              1<<0
//-------------------------------------------------
// APIs
//-------------------------------------------------
/**************************************************************
 * @Fn			-MCAL_SPI_INIT
 * @Breif		-Initializes the SPI according to specified parameters
 * @Param [in]		-SPIx where x can be (1,2,3 depending on device used)
 * @Param [in]		-Config pointer to SPI_Config_t structure that contains the configuration information for the specified SPI
 * @Retval 		-None
 * Note			-Support for SPI Full duplex Master/Slave only & NSS HW only for slave
 */
void MCAL_SPI_INIT (SPI_Typedef* SPIx, SPI_Config_t* SPI_Config)
{
	//Safety for regs
	uint16_t tmpreg_CR1=0;
	uint16_t tmpreg_CR2=0;

	if (SPIx == SPI1)
	{
		Global_SPI_Config[SPI1_INDEX] = SPI_Config;
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2)
	{
		Global_SPI_Config[SPI2_INDEX] = SPI_Config;
		RCC_SPI2_CLK_EN();
	}
	//EN SPI CR1:Bit 6 SPE
		tmpreg_CR1= (0x1U<<6);

	//Master or slave
	tmpreg_CR1 |= SPI_Config->DEVICE_MODE;

	//Communication mode
	tmpreg_CR1 |= SPI_Config->COMM_MODE;

	//Data size
	tmpreg_CR1 |= SPI_Config->DATA_SZ;

	//SPI CLK_POLARITY
	tmpreg_CR1 |= SPI_Config->CLK_POLARITY;

	//SPI CLK_PHASE
	tmpreg_CR1 |= SPI_Config->CLK_PHASE;

	//Frame format
	tmpreg_CR1 |= SPI_Config->FRAME_FORMAT;


	//NSS

	if (SPI_Config->NSS == SPI_NSS_HW_MASTER_SSO_ENABLE)
	{
		tmpreg_CR2 |= SPI_Config->NSS;
	}
	else if ((SPI_Config->NSS == SPI_NSS_HW_MASTER_SSO_DISABLE) || (SPI_Config->NSS == SPI_NSS_HW_SLAVE))
	{
		tmpreg_CR2 &= SPI_Config->NSS;
	}

	else
	{
		tmpreg_CR1 |= SPI_Config->NSS;
	}

	// SPI BaudRate prescalar
	tmpreg_CR1 |= SPI_Config->SPI_BAUDRATE_PRESCALAR;


	// SPI_IRQ_ ENABLE/DISABLE
	if (SPI_Config->IRQ_ENABLE !=  SPI_IRQ_ENABLE_NONE)
	{
		tmpreg_CR2 |= SPI_Config->IRQ_ENABLE;
		if (SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_ENABLE;
		}
		else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_ENABLE;
		}

	}

	SPIx->CR1 = tmpreg_CR1;
	SPIx->CR2 = tmpreg_CR2;


	//SPIx->I2SCFGR &= ~(1<<11);
	//SPIx->CRCPR = 0x0;

}

/**************************************************************
 * @Fn			-MCAL_SPI_DeINIT
 * @Breif		-Deinitializes the SPI (
 * @Param [in]		-SPIx where x can be (1,2,3 depending on device used)
 * @Retval 		-None
 * Note			-Reset model by RCC
 */

void MCAL_SPI_DeINIT (SPI_Typedef* SPIx)
{
	if (SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_DISABLE;
		RCC_SPI1_RESET();
	}
	else if(SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_DISABLE;
		RCC_SPI2_RESET();
	}

}

/**************************************************************
 * @Fn			-MCAL_SPI_GPIO_SET_PINS
 * @Breif		-Initializes GPIO pins
 * @Param [in]		-SPIx where x can be (1,2,3 depending on device used)
 * @Retval 		-None
 * Note			-Check pin alternative table
 */
void MCAL_SPI_GPIO_SET_PINS(SPI_Typedef* SPIx)
{
	GPIO_PIN_CONFIG_t PinCfg;

	if (SPIx == SPI1)
	{
		//PA4:SPI1_NSS
		//PA5:SPI1_SCK
		//PA6:SPI_MISO
		//PA7:SPI_MOSI

		if (Global_SPI_Config[SPI1_INDEX]->DEVICE_MODE == SPI_DEVICE_MODE_MASTER)
		{
			//PA4:SPI1_NSS
			switch (Global_SPI_Config[SPI1_INDEX]->NSS)
			{
				case SPI_NSS_HW_MASTER_SSO_DISABLE:
				//Hardware master /slave Input floating
				PinCfg.GPIO_PIN_NO = GPIO_PIN4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;

				case SPI_NSS_HW_MASTER_SSO_ENABLE:
				//Hardware master/ NSS output enabled Alternate function push-pull
				PinCfg.GPIO_PIN_NO = GPIO_PIN4;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;
				default:
					break;
			}

			//PA5:SPI1_SCK
			//Master Alternate function push-pull
			PinCfg.GPIO_PIN_NO = GPIO_PIN5;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA6:SPI_MISO
			//Supported only (Full Duplex) master: Input floating
			PinCfg.GPIO_PIN_NO = GPIO_PIN6;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA7:SPI_MOSI
			//Supported only (Full Duplex) master: Alternate function push-pull
			PinCfg.GPIO_PIN_NO = GPIO_PIN7;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}


		else if (Global_SPI_Config[SPI1_INDEX]->DEVICE_MODE == SPI_DEVICE_MODE_SLAVE)
		{
			//PA4:SPI1_NSS
			if (Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_HW_SLAVE )
			{	//Hardware master /slave Input floating
				PinCfg.GPIO_PIN_NO = GPIO_PIN4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}
			//PA5:SPI1_SCK
			//Slave Input floating
			PinCfg.GPIO_PIN_NO = GPIO_PIN5;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA6:SPI_MISO
			//Supported only (Full Duplex) slave:  Alternate function push-pull
			PinCfg.GPIO_PIN_NO = GPIO_PIN6;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//PA7:SPI_MOSI
			//Supported only (Full Duplex) slave: Input floating
			PinCfg.GPIO_PIN_NO = GPIO_PIN7;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}


	}
	else if(SPIx == SPI2)
	{
		//PB12:SPI1_NSS
		//PB13:SPI1_SCK
		//PB14:SPI_MISO
		//PB15:SPI_MOSI


		if (Global_SPI_Config[SPI2_INDEX]->DEVICE_MODE == SPI_DEVICE_MODE_MASTER)
		{
			//PB12:SPI1_NSS
			switch (Global_SPI_Config[SPI2_INDEX]->NSS)
			{
				case SPI_NSS_HW_MASTER_SSO_DISABLE:
				//Hardware master /slave Input floating
				PinCfg.GPIO_PIN_NO = GPIO_PIN12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break;

				case SPI_NSS_HW_MASTER_SSO_ENABLE:
				//Hardware master/ NSS output enabled Alternate function push-pull
				PinCfg.GPIO_PIN_NO = GPIO_PIN12;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break;
			}

			//PB13:SPI1_SCK
			//Master Alternate function push-pull
			PinCfg.GPIO_PIN_NO = GPIO_PIN13;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB14:SPI_MISO
			//Supported only (Full Duplex) master: Input floating
			PinCfg.GPIO_PIN_NO = GPIO_PIN14;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB15:SPI_MOSI
			//Supported only (Full Duplex) master: Alternate function push-pull
			PinCfg.GPIO_PIN_NO = GPIO_PIN15;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}


		else if (Global_SPI_Config[SPI2_INDEX]->DEVICE_MODE == SPI_DEVICE_MODE_SLAVE)
		{
			//PB12:SPI1_NSS
			if (Global_SPI_Config[SPI2_INDEX]->NSS == SPI_NSS_HW_SLAVE )
			{	//Hardware master /slave Input floating
				PinCfg.GPIO_PIN_NO = GPIO_PIN12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}
			//PB13:SPI1_SCK
			//Slave Input floating
			PinCfg.GPIO_PIN_NO = GPIO_PIN13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB14:SPI_MISO
			//Supported only (Full Duplex) slave:  Alternate function push-pull
			PinCfg.GPIO_PIN_NO = GPIO_PIN14;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//PB15:SPI_MOSI
			//Supported only (Full Duplex) slave: Input floating
			PinCfg.GPIO_PIN_NO = GPIO_PIN15;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}

	}
}


/**************************************************************
 * @Fn				-MCAL_SPI_SEND_DATA
 * @Breif			-Send Buffer on SPI
 * @Param [in]		-SPUx where x can be (1,2,3 depending on device used)
 * @Param [in]		-pTX_Buffer buffer
 * @Param [in]		-ENUM to check if polling mechanism is enabled
 * @Retval 			-None
 * Note				-Should initialize SPI first
 *
 */

void MCAL_SPI_SEND_DATA (SPI_Typedef* SPIx, uint16_t* pTX_Buffer, Polling_Mechanism PollingEn)
{
	//TODO check if transmit only or recieve only
	if ( PollingEn == Polling_enable)
		while( !((SPIx->SR) &  SPI_SR_TXE) );

	SPIx->DR = *pTX_Buffer;

}


/**************************************************************
 * @Fn			-MCAL_SPI_RECEIVE_DATA
 * @Breif		-Receive Buffer on SPI
 * @Param [in]		-SPIx where x can be (1,2,3 depending on device used)
 * @Param [in]		-pTX_Buffer buffer
 * @Param [in]		-ENUM to check if polling mechanism is enabled
 * @Retval 		-None
 * Note			-Should initialize SPI first
 */
void MCAL_SPI_RECEIVE_DATA (SPI_Typedef* SPIx, uint16_t* pTX_Buffer,  Polling_Mechanism PollingEn)
{
	if ( PollingEn == Polling_enable)
		while( !((SPIx->SR) & SPI_SR_RXNE));

	 *pTX_Buffer = SPIx->DR;
}

void MCAL_SPI_TX_RX (SPI_Typedef* SPIx,uint16_t* pTX_Buffer,  Polling_Mechanism PollingEn)
{

	if ( PollingEn == Polling_enable)
			while( !((SPIx->SR ) &  SPI_SR_TXE) );
		SPIx->DR = *pTX_Buffer;

	if ( PollingEn == Polling_enable)
		while( !((SPIx->SR) & SPI_SR_RXNE) );
	*pTX_Buffer = SPIx->DR;






}


//-------------------------------------------------
// IRQ
//-------------------------------------------------

void SPI1_IRQHandler(void)
{
	S_IRQ_SRC irq_src;

	irq_src.TXE =  (SPI1->SR & (1<<1) >> 1 );
	irq_src.RXNE =  (SPI1->SR & (1<<0) >> 0 );
	irq_src.ERRI =  (SPI1->SR & (1<<4) >> 4 );

	Global_SPI_Config[SPI1_INDEX]->P_SPI_IRQ_CALLBACK(irq_src);
}

void SPI2_IRQHandler(void)
{
	S_IRQ_SRC irq_src;

	irq_src.TXE = (SPI2->SR & (1<<1) >> 1 );
 	irq_src.RXNE = (SPI2->SR & (1<<0) >> 0 );
	irq_src.ERRI = (SPI2->SR & (1<<4) >> 4 );

	Global_SPI_Config[SPI2_INDEX]->P_SPI_IRQ_CALLBACK(irq_src);
}

