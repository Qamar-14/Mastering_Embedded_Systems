#include "stdio.h"
#include "stdlib.h"

int main()
{
	  int number, number2;

	  printf("Enter two integers: ");
	  fflush(stdout); fflush(stdin);
	  scanf("%d \r\n %d", &number, &number2);

	  printf("Sum: %d", number+number2);


	  return 0;

	}
