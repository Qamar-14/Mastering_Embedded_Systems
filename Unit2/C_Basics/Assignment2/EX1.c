#include "stdio.h"
#include "stdlib.h"

void main()
{
	int x ;

	printf("Enter an integer you want to check: ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &x);

	if ((x % 2) ==0)
	{
		printf("%d is even",x);
	}

	else
	{
		printf("%d is odd",x);
	}


}
