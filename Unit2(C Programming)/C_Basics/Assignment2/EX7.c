#include "stdio.h"
#include "stdlib.h"

void main()
{
	int x, factorial=1;
	printf("Enter an integer: ");
	fflush(stdout); fflush(stdin);
	scanf("%d", &x);
	if ( x<0){
		printf("Error!! Factorial of negative number doesn't exist.");
	}
	else if (x==0){
		printf("Factorial =1 ");
	}
	else{
		for ( int i =1; i<=x;i++){
			factorial = factorial*i;
		}
		printf("factorial= %d" ,factorial);
	}



}




