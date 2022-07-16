#include "stdio.h"
#include "stdlib.h"

void main()
{
	float x,y,z;
	printf("Enter 3 numbers: ");
	fflush(stdout); fflush(stdin);
	scanf("%f \r\n %f \r\n %f", &x, &y, &z);
	if (x>y){
		if (x>z){
			printf("Largest Number is: %f", x);
		}
		else {
			printf("Largest Number is: %f", z);
		}
	}
	else {
		if (y>z){
			printf("Largest Number is: %f", y);
		}
		else {
			printf("Largest Number is: %f", z);
		}
	}
}




