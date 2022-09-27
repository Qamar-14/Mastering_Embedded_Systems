#include "uart.h"

unsigned char string_buffer[100] = "Qamar Elgohary";
unsigned char stringBuffer2[100]; //" .bss Section in RAM";
unsigned char const stringBuffer3[100] = "rodata Section";
void main(void)
{
	Uart_Send_string (string_buffer);
}