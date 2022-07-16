/*
 * main.c
 *
 *  Created on: Jul 13, 2022
 *      Author: Qamar
 */

#include "stdio.h"
#include "stdlib.h"

int main()
{
	  int number;

	  printf("Enter an integer: ");
	  fflush(stdout); fflush(stdin);


	  scanf("%d", &number);

	  printf("Integer entered by user: %d", number);


	  return 0;

	}
