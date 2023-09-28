#include "stdio.h"


int main() {
	int m = 29;
	int *ab;

	printf("Address of m : %p",&m);
	printf("\nValue of m : %d\n",m);

	ab = &m;
	printf("\nAddress of pointer ab : %p",ab);
	printf("\nContent of pointer ab : %d\n",*ab);

	m =34;
	printf("\nAddress of pointer ab : %p",ab);
	printf("\nContent of pointer ab : %d\n",*ab);

	*ab = 7;
	printf("\nAddress of m : %p",&m);
	printf("\nValue of m : %d",m);


	return 0;
}



