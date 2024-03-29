/*
 *
 * LCD_driver.h
 *
 *
 *	Created on: 7/22/2023
 *	Author: Qamar Elgohary
 *	Mastering Embedded Systems
 */

#ifndef LCD_H_
#define LCD_H_

#define F_CPU 1000000UL

//-------------------------------------------------
// INCLUDES
//-------------------------------------------------

#include "GPIO_DRIVER/gpio.h"


#define LCD_CTRL		GPIOA
#define RS_SWITCH		GPIO_PIN8
#define RW_SWITCH 		GPIO_PIN9
#define EN_SWITCH 		GPIO_PIN10
#define DATA_shift		4 		// in 8 bit mode 0 and in 4 bit mode 4

#define LCD_FUNCTION_8BIT_2LINES   				(0x38)
#define LCD_FUNCTION_4BIT_2LINES   				(0x28)
#define LCD_MOVE_DISP_RIGHT       				(0x1C)
#define LCD_MOVE_DISP_LEFT   					(0x18)
#define LCD_MOVE_CURSOR_RIGHT   				(0x14)
#define LCD_MOVE_CURSOR_LEFT 	  				(0x10)
#define LCD_DISP_OFF   							(0x08)
#define LCD_DISP_ON_CURSOR   					(0x0E)
#define LCD_DISP_ON_CURSOR_BLINK   				(0x0F)
#define LCD_DISP_ON_BLINK   					(0x0D)
#define LCD_DISP_ON   							(0x0C)
#define LCD_ENTRY_DEC   						(0x04)
#define LCD_ENTRY_DEC_SHIFT   					(0x05)
#define LCD_ENTRY_INC_   						(0x06)
#define LCD_ENTRY_INC_SHIFT   					(0x07)
#define LCD_BEGIN_AT_FIRST_ROW					((uint16_t)0x80u)
#define LCD_BEGIN_AT_SECOND_ROW					((uint16_t)0xC0u)
#define LCD_CLEAR_SCREEN						(0x01)
#define LCD_ENTRY_MODE							(0x06)


//-------------------------------------------------
// LCD FUNCTIONS
//-------------------------------------------------


void LCD_INIT(void);

void LCD_WRITE_COMMAND(unsigned char command);

void LCD_WRITE_CHAR(unsigned char character);

void LCD_WRITE_STRING(char* string);

void LCD_IsBusy(void);
void LCD_kick(void);
void LCD_clear_screen(void);
void LCD_GOTO_XY(unsigned char line, unsigned char position);

void DISPLAY_NUMBER(int num);
void DISPLAY_REAL_NUMBER(double num);

void LCD_WRITE_STRING_POS(char* string, uint16_t x,unsigned char y);


void delay_ms(uint32_t time);

#endif
