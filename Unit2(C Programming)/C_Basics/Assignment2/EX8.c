#include "stdio.h"
#include "stdlib.h"

void main()
{
	char x;
	float y, z;
	printf("Enter an operator either + or - or * or divide: ");
	fflush(stdout); fflush(stdin);
	scanf("%c", &x);

	printf("Enter two operands ");
	fflush(stdout); fflush(stdin);
	scanf("%f \r\n %f", &y, &z);

	switch(x)
	{
	case '+':
		printf("%.1f + %.1f = %.1f",y ,z, y+z );
		break;
	case '-':
		printf("%.1f - %.1f = %.1f",y ,z, y-z );
		break;
	case '*':
		printf("%.1f + %.1f = %.1f",y ,z, y*z );
		break;
	case '/':
		printf("%.1f + %.1f = %.1f",y ,z, y/z );
		break;

	default:
		printf("Error! Operator is not correct." );
		break;
	}
}




