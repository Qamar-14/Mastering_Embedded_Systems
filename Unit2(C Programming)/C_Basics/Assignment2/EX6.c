#include "stdio.h"
#include "stdlib.h"

void main()
{
	int x, sum=0;
	printf("Enter a number: ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &x);
	for ( int i =1; i<=x;i++){
		sum = sum +i;
	}
	printf("sum: %d" ,sum);


}




