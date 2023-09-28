#include "stdio.h"
#include "stdlib.h"

int main()
{
	int i, n;
	float x[100], sum=0.0, average;


	printf("Enter the numbers of data \n");
	fflush(stdout); fflush(stdin);

	scanf("%d ", &n);

	if (n>100 || n<=0)
	{
		printf("Error, Number out of range. Please enter the number again");
		scanf("%d",&n);
	}
	else
	{
		for (i=0;i<n;i++)
		{
			printf("%d. Enter number: ", i+1);
			scanf("%f ", &x[i]);
			fflush(stdout); fflush(stdin);

		}
	}

	for (i=0;i<n;i++)
	{
		sum = sum + x[i];
	}
	average = sum/n;

	printf("\nAverage = %.2f ", average);

	return 0;
}




