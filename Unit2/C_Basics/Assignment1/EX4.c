#include "stdio.h"
#include "stdlib.h"

int main()
{
	  float number, number2;

	  printf("Enter two numbers: ");
	  fflush(stdout); fflush(stdin);
	  scanf("%f \r\n %f", &number, &number2);

	  printf("Product: %f", number*number2);


	  return 0;

	}
