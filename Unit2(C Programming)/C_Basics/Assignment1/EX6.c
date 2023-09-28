#include "stdio.h"
#include "stdlib.h"

void main()
{
	  float x ,y;

	  printf("Enter value of a: ");
	  fflush(stdout); fflush(stdin);
	  scanf("%f", &x);

	  printf("Enter value of b: ");
	  fflush(stdout); fflush(stdin);
	  scanf("%f", &y);

	  x = x + y;
	  y = x - y;
	  x = x - y;

	  printf("After swapping, value of a = %.2f " ,x);
	  printf("After swapping, value of b = %.2f " ,y);

	}
