/*
 * main.c
 *
 * Created on: Oct 4, 2022
 *     Author: Qamar
 */

#include "fifo/fifo.h"

void main (){

	FIFO_Buf_t FIFO_UART;
	int i , *temp;

	if(FIFO_init (&FIFO_UART, UART_buffer, 5)== FIFO_no_error)
		printf("FIFO_init ----- Done \n");

	for(i=0;i<7;i++)
	{
		printf("FIFO Enqueue (%x) \n",i);
		if(FIFO_enqueue (&FIFO_UART, i)== FIFO_no_error)
			printf("FIFO_enqueu ---- Done \n");
		else
			printf("FIFO_enqueu ----- Failed \n");
	}
	FIFO_PRINT(&FIFO_UART);

	if(FIFO_dequeue (&FIFO_UART, &temp)== FIFO_no_error)
		printf("FIFO_dequeu %x ---- Done \n", *temp);
	else
		printf("FIFO_dequeu %x ----- Failed \n", *temp);
	FIFO_PRINT(&FIFO_UART);
}
