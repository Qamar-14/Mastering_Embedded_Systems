#include "stdio.h"
#include "stdlib.h"

int main()
{
	int i, n, location, element, x[100];



	printf("Enter number of elements: ");
	fflush(stdout); fflush(stdin);

	scanf("%d \r\n", &n);


	if (n>100 || n<=0 )
	{
		printf("Error, Number out of range. Please enter the number of rows and columns again");
		scanf("%d \r\n", &n);
	}
	else
	{
		for (i=0;i<n;++i)
		{
			scanf("%d ", &x[i]);
		}
	}
	printf("Enter the element to be searched: \n ");
	fflush(stdout); fflush(stdin);
	scanf("%d ", &element);

	for(i=0;i<=n-1;i++)
	{
		if (x[i] == element)
		{
			location = i + 1;
			break;
		}
	}

	if (location < n){
	printf("Number found at location: %d\n ", location);
	fflush(stdout); fflush(stdin);
	}
	else
		printf("Number not found \n ");
	return 0;
}




