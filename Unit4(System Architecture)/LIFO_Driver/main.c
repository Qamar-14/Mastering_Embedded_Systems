/*
 * lifo.h
 *
 * Created on: Oct 4, 2022
 *     Author: Qamar
 */

#include "lifo.h"

unsigned int buffer1 [5]; //5*4=20 BYTES


void main ()
{
	unsigned int i , temp=0;
	LIFO_Buf_t uart_lifo, I2C_lifo;
	//Static Allocation
	LIFO_init(&uart_lifo, buffer1, 5);
	//Dynamic Allocation
	unsigned int* buffer2 = (unsigned int*) malloc (5 * sizeof(unsigned int)); //5*4 = 20
	LIFO_init(&I2C_lifo, buffer2, 5);

	for (i=0; i<5; i++){
		if (LIFO_Add_Item(&uart_lifo, i)== LIFO_no_error){
			printf("UART_LIFO add : %d \n", i);
			fflush(stdout);
		}
	}
	for (i=0; i<5; i++){
			if(LIFO_Get_Item(&uart_lifo, &temp)== LIFO_no_error){
				printf("UART_LIFO get : %d \n", temp);
				fflush(stdout);
		}
	}

}
