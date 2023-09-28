#include "stdio.h"
#include "stdlib.h"
#include "string.h"



int main()
{
	struct Distance{

		float feet;
		float inch;

	}d1,d2,sum;
	printf("Enter information of 1st distance:\n");
	printf("Enter feet:");
	fflush(stdout);
	scanf("%f", &d1.feet);

	printf("Enter inch: ");
	fflush(stdout);
	scanf("%f",&d1.inch);

	printf("Enter information of 2nd distance:\n");
	printf("Enter feet:");
	fflush(stdout);
	scanf("%f", &d2.feet);

	printf("Enter inch: ");
	fflush(stdout);
	scanf("%f",&d2.inch);


	fflush(stdout);
	sum.feet = (d1.feet + d2.feet);
	sum.inch = (d1.inch + d2.inch);
	if (sum.inch>12){
		sum.feet++;
		sum.inch = sum.inch-12;

	}

	printf("Sum of distances = %0.2f'%0.2f\n", sum.feet,sum.inch);

	fflush(stdout);


	/*union a{
		int i;
		char ep[2];

	};

	union a u1 = {512};
	union a u2 ={'0','2'};*/
	return 0;
}






