/*
 *
 * LCD_driver.c HD44780
 *
 *
 *	Created on: 7/22/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */

//-------------------------------------------------
// INCLUDES
//-------------------------------------------------

#include "lcd.h"

#include <STM32F103.h>

#include "lcd.h"



void delay_ms(uint32_t time) {
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++)
			;
}

GPIO_PIN_CONFIG_t PinCfg ;


/**************************************************************
 * @Fn			-LCD_GPIO_Init
 * @Breif		-Initializes the GPIOx PINs connected to the LCD
 * @Param [in]		-None
 * @Retval 		-None
 * Note			-
 */


void LCD_GPIO_Init() {

	PinCfg.GPIO_PIN_NO = GPIO_PIN8;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED =GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN9;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED =GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN10;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);


	PinCfg.GPIO_PIN_NO = GPIO_PIN0;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN2;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);


	PinCfg.GPIO_PIN_NO = GPIO_PIN3;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN4;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED= GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN5;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN6;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN7;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);



	//MCAL_GPIO_WRITE_PIN (LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
	//MCAL_GPIO_WRITE_PIN(LCD_CTRL, GPIO_PIN8, GPIO_PIN_RESET);
	//MCAL_GPIO_WRITE_PIN(LCD_CTRL, GPIO_PIN9, GPIO_PIN_RESET);
	//MCAL_GPIO_WRITE_PIN (LCD_CTRL, GPIO_PIN10, GPIO_PIN_RESET);

}


/**************************************************************
 * @Fn			-LCD_IsBusy
 * @Breif		-Checks whether the LCD is busy or not
 * @Param [in]		-None
 * @Retval 		-None
 * Note			-
 */

void LCD_IsBusy()
{
	//(1) to make sure the LCD is not busy
	//a. set the port to receive data on the microcontroller (Data direction as input).

	PinCfg.GPIO_PIN_NO = GPIO_PIN0;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN1;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN2;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN3;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN4;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN5;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN6;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN7;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOATING;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);



	//b. put the LCD in read mode (RW on).
	MCAL_GPIO_WRITE_PIN (LCD_CTRL, RW_SWITCH, GPIO_PIN_SET);

	//c. put the LCD in command mode (RS off).
	MCAL_GPIO_WRITE_PIN (LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);

	LCD_kick();


	//return to output mode
	PinCfg.GPIO_PIN_NO = GPIO_PIN0;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN1;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN2;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN3;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN4;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED= GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN5;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN6;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	PinCfg.GPIO_PIN_NO = GPIO_PIN7;
	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
	MCAL_GPIO_Init(LCD_CTRL, &PinCfg);

	MCAL_GPIO_WRITE_PIN (LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);

	//LCD_GPIO_Init();

}


/**************************************************************
 * @Fn			-LCD_kick
 * @Breif		-turn on the enable and then turn it off.(delay ~500ns)
 * @Param [in]	-None
 * @Retval 		-None
 * Note			-
 */

void LCD_kick() {
	MCAL_GPIO_WRITE_PIN(LCD_CTRL, EN_SWITCH, GPIO_PIN_SET);
	delay_ms(50);
	MCAL_GPIO_WRITE_PIN(LCD_CTRL, EN_SWITCH, GPIO_PIN_RESET);
}


/**************************************************************
 * @Fn			-LCD_INIT
 * @Breif		-Initializes the LCD
 * @Param [in]		-None
 * @Retval 		-None
 * Note			-
 */


void LCD_INIT() {

	delay_ms(20);

	//============================
	LCD_GPIO_Init();
	delay_ms(15);

	//8 bit mode
	//LCD_clear_screen();
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
}

/**************************************************************
 * @Fn			-LCD_WRITE_COMMAND
 * @Breif		-
 * @Param [in]	-Command
 * @Retval 		-None
 * Note			-(2) Control the LCD's cursor, or display function is not busy (Send a command to the LCD)
				• set the port direction as output so you can send information to the LCD.
				• turn RW off so you can write.
				• turn RS off for command mode.
				• Write the command on D0...D7
				• turn on the enable and then turn it off.(delay ~500ns)
				The LCD will magically perform the command.
 */


void LCD_WRITE_COMMAND(unsigned char command) {

	//LCD_IsBusy();

	MCAL_GPIO_WRITE_PORT(LCD_CTRL, command);


	MCAL_GPIO_WRITE_PIN(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WRITE_PIN(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);



	delay_ms(15);
	LCD_kick();

}

/**************************************************************
 * @Fn			-LCD_WRITE_CHAR
 * @Breif		-This is the same as sending a command except the RS is on and the port will equalthe character corresponding to the ASCII code.
 * @Param [in]	-Character to display
 * @Retval 		-None
 * Note			-(3) Write a character to the LCD for it to display Send a character to the LCD: This is the same as sending a command except the RS is on and the port will equal the character corresponding to the ASCII code.
				• set the port direction as output so you can send information to the LCD.
				• turn RW off so you can write.
				• turn RS ON for Data mode.
				• Write the command on D0...D7
				• turn on the enable and then turn it off.(delay ~500ns)
*/


void LCD_WRITE_CHAR(unsigned char character) {

	//LCD_IsBusy();

	MCAL_GPIO_WRITE_PORT(LCD_CTRL, character);

	MCAL_GPIO_WRITE_PIN(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WRITE_PIN(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET);


	delay_ms(15);
	LCD_kick();
}

/**************************************************************
 * @Fn			-LCD_WRITE_STRING
 * @Breif		-
 * @Param [in]		-String to display
 * @Retval 		-None
 * Note			-
 */
void LCD_WRITE_STRING(char *string)
 {
	int count = 0;
  	while (*string > 0)
	{
		count++;
		LCD_WRITE_CHAR(*string++);
		if (count == 16)
		{
			LCD_GOTO_XY(2, 0);
		}
		else if (count == 32)
		 {
			LCD_clear_screen();
			LCD_GOTO_XY(1, 0);
			count = 0;
		}
	}
}

/**************************************************************
 * @Fn			-LCD_CLEAR_SCREEN
 * @Breif		- clears screen
 * @Param [in]		-None
 * @Retval 		-None
 * Note			-
 */
void LCD_clear_screen() {
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}

/**************************************************************
 * @Fn			-LCD_GOTO_XY
 * @Breif		-Sets cursor at the specified (x,y) position
 * @Param [in]	-row
 * @Param [in]	-column
 * @Retval 		-None
 * Note			-
 */
void LCD_GOTO_XY(unsigned char line, unsigned char position) {
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW + position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0) {
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW + position);
		}
	}
}




void DISPLAY_NUMBER(int num)
{
	char str[7];
    sprintf(str, "%d", num);

    // The string "" is stored into str
    LCD_WRITE_STRING(str);

}
void DISPLAY_REAL_NUMBER(double num)
{
	char *tmpSign = (num < 0)? "-": "";
	float value = (num < 0)? -num: num;

	int int_value = value; // the int value of the number
	float decimal_part= value - int_value; // the fraction part

	int tmp_int = decimal_part*1000; //turn into int


	char str[16];
	sprintf(str, "%s%d.%04d", tmpSign,int_value,tmp_int);

	// The string "" is stored into str
	LCD_WRITE_STRING(str);
}

