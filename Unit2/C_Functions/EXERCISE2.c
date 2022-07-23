#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int factorial(int number)
{
	if(number!=1)
	  {return (number*factorial(number-1));}
}

int main()
{
	int i;
	printf("Enter a positive integer:" );
	fflush(stdout);
	scanf("%d ",&i);

	printf("Factorial of %d is %1d: ", i,factorial(i));
	fflush(stdout);

	return 0;
}

