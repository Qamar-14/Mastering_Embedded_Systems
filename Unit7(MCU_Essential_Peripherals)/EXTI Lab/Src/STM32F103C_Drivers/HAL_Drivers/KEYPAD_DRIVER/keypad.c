/*
 *
 * keypad_driver.c
 *
 *
 *	Created on: 7/23/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */

//-------------------------------------------------
// INCLUDES
//-------------------------------------------------
#include "../../../../../stm32/Src/STM32F103C_Drivers/HAL_Drivers/KEYPAD_DRIVER/keypad.h"

GPIO_PIN_CONFIG_t PinCfg ;

int keypad_row[]={R0,R1,R2,R3};
int keypad_column[]={C0,C1,C2,C3};


/**************************************************************
 * @Fn			- KEYPAD_INIT
 * @Breif		-
 * @Param [in]	-none
 * @Retval 		-none
 * Note			-The keypad here has four columns and four rows, for identification of button
				pressed, we are going to use cross reference method. Here first we are going to either
				connect all columns or all rows to vcc, so if rows are connected to common vcc, we
				are going to take the columns as inputs to controller.
 */

void KEYPAD_INIT(void)
{
	//set upper part of keypad port as input.
	//this will be required for scanning the rows
	PinCfg.GPIO_PIN_NO = R0;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_NO = R1;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_NO = R2;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_NO = R3;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);


	//set lower part of keypad port as output.
	//part of keypad where the rows are connected
	PinCfg.GPIO_PIN_NO = C0;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_NO = C1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_NO = C2;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);

	PinCfg.GPIO_PIN_NO = C3;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinCfg);


	MCAL_GPIO_WRITE_PORT(KEYPAD_PORT, 0xFF);

}

/**************************************************************
 * @Fn			- KEYPAD_GET_KEY
 * @Breif		-
 * @Param [in]	-none
 * @Retval 		-char
 * Note			-
 */

char KEYPAD_GET_KEY(void)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{

		MCAL_GPIO_WRITE_PIN(KEYPAD_PORT, keypad_column[0], GPIO_PIN_SET);
		MCAL_GPIO_WRITE_PIN(KEYPAD_PORT, keypad_column[1], GPIO_PIN_SET);
		MCAL_GPIO_WRITE_PIN(KEYPAD_PORT, keypad_column[2], GPIO_PIN_SET);
		MCAL_GPIO_WRITE_PIN(KEYPAD_PORT, keypad_column[3], GPIO_PIN_SET);

		MCAL_GPIO_WRITE_PIN(KEYPAD_PORT, keypad_column[i], GPIO_PIN_RESET);
		for (j = 0; j < 4; j++)
		{
			if (MCAL_GPIO_READ_PIN (KEYPAD_PORT, keypad_row[j]) == 0)
			{
				while (MCAL_GPIO_READ_PIN (KEYPAD_PORT, keypad_row[j]) == 0);//wait for key to be released (single press)
				switch (i)
				{
					case (0):
						if (j == 0)
							return '7';
						else if (j == 1)
							return '4';
						else if (j == 2)
							return '1';
						else if (j == 3)
							return '?';
						break;
					case (1):
						if (j == 0)
							return '8';
						else if (j == 1)
							return '5';
						else if (j == 2)
							return '2';
						else if (j == 3)
							return '0';
						break;
					case (2):
						if (j == 0)
							return '9';
						else if (j == 1)
							return '6';
						else if (j == 2)
							return '3';
						else if (j == 3)
							return '=';
						break;
					case (3):
						if (j == 0)
							return '/';
						else if (j == 1)
							return '*';
						else if (j == 2)
							return '-';
						else if (j == 3)
							return '+';
						break;
					}
			}
		}
	}
	return 'A';
}

