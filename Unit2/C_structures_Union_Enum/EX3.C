#include "stdio.h"
#include "stdlib.h"
#include "string.h"



int main()
{
	struct ComplexNumber{

		float real;
		float imaginary;

	}d1,d2,sum;
	printf("For first complex number:\n");
	printf("Enter real and imaginary respectively:");
	fflush(stdout);
	scanf("%f\n %f", &d1.real, &d1.imaginary);

	printf("For second complex number:\n");
	printf("Enter real and imaginary respectively:");
	fflush(stdout);
	scanf("%f\n %f", &d2.real, &d2.imaginary);




	fflush(stdout);
	sum.real = (d1.real + d2.real);
	sum.imaginary = (d1.imaginary + d2.imaginary);


	printf("Sum = %0.2f + %0.2fi\n", sum.real,sum.imaginary);

	fflush(stdout);


	return 0;
}






