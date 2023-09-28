/*
 * fifo.h
 *
 * Created on: Oct 4, 2022
 *     Author: Qamar
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"

// USER Configurations
// Select the element type (uint8_t , uint16_t, uint32_t..)


#define element_type uint8_t

//create buffer
#define width1 5
element_type UART_buffer[width1];

//FIFO Data Types

typedef struct{
	unsigned int length;
	unsigned int count;
	element_type* base;
	element_type* head;
	element_type* tail;
}FIFO_Buf_t;

typedef enum{
	FIFO_no_error, FIFO_full, FIFO_empty, FIFO_Null
}FIFO_status;

//FIFO APIs
FIFO_status FIFO_init(FIFO_Buf_t* fifo, element_type* buf, uint32_t length );
FIFO_status FIFO_enqueue(FIFO_Buf_t* fifo,element_type item);
FIFO_status FIFO_dequeue(FIFO_Buf_t* fifo, element_type* item);
FIFO_status FIFO_IS_FULL(FIFO_Buf_t* fifo);
FIFO_status FIFO_PRINT(FIFO_Buf_t* fifo);

#endif /* FIFO_H_ */
