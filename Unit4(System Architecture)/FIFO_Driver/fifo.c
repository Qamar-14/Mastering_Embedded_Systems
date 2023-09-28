/*
 * fifo.h
 *
 * Created on: Oct 4, 2022
 *     Author: Qamar
 */
#include "fifo.h"

//APIs
FIFO_status FIFO_init(FIFO_Buf_t* fifo, element_type* buf, unsigned int length ){
	if (buf == NULL)
		return FIFO_Null;
	fifo->base = buf;
	fifo->head = buf;
	fifo->tail = buf;
	fifo->length = length;
	fifo->count = 0;

	return FIFO_no_error ;
}

FIFO_status FIFO_enqueue(FIFO_Buf_t* fifo, element_type item){
	if (!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;

	//Fifo is full
	if (FIFO_IS_FULL(fifo) == FIFO_full )
		return FIFO_full;

	*(fifo->head) = item;
	fifo->count ++;

	//circular fifo
	if(fifo->head == (fifo->base +(fifo->length * sizeof(element_type))))
		fifo->head = fifo->base;
	else
		fifo->head++;
	return FIFO_no_error;
}
FIFO_status FIFO_dequeue(FIFO_Buf_t* fifo, element_type* item){
	//fifo is full
	if (FIFO_IS_FULL(fifo) == FIFO_full )
		return FIFO_full;

	if (fifo->count == 0)
		return FIFO_empty;

	*item = *(fifo->tail);
	fifo->count-- ;

	//circular fifo
	if(fifo->tail == (fifo->base +(fifo->length * sizeof(element_type))))
		fifo->tail = fifo->base;
	else
		fifo->tail++;

	return FIFO_no_error;

}
FIFO_status FIFO_IS_FULL(FIFO_Buf_t* fifo){
	if (!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_Null;
	if (fifo->count == fifo->length)
		return FIFO_full;
	return FIFO_no_error;


}
FIFO_status FIFO_PRINT(FIFO_Buf_t* fifo){
	element_type* temp ;
	int i ;
	if(fifo->count ==0)
		printf("FIFO is empty!\n");
	else {
		temp = fifo->tail ;
		printf("\n --------FIFO_PRINT-------");
		for(i=0; i<fifo->count; i++){
			printf("\t %x \n", *temp);
			temp++;
		}
		printf("------------\n");
	}
}
