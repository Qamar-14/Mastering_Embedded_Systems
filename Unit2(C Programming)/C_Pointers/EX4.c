#include "stdio.h"


int main() {
	int elements[15];
	int i,j=0;
	int *ptr = elements;

	printf("Input the number of elements to store in the array (max 15) : ");
	fflush(stdout);
	scanf("%d",&j);


	printf("\nInput %d number of elements in the array : \n",j);
	fflush(stdout);

	for (i =0; i<j ; i++){
		printf("element - %d : ", i+1);
		fflush(stdout);
		scanf("%d" ,ptr);
		ptr++;
	}


	printf("\nThe elements of array in reverse order are :\n");
	fflush(stdout);
	int length =j;
	for (i =0; i<length ; i++){
		ptr--;
		printf("element - %d : %d\n", j--,*ptr);
		fflush(stdout);

	}


	return 0;
}



