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
		printf("Enter the element to be inserted: \n ");
		fflush(stdout); fflush(stdin);
		scanf("%d ", &element);
	
	
		printf("Enter the location: \n ");
		fflush(stdout); fflush(stdin);
		scanf("%d ", &location);
	
		for(i=n-1;i>=location-1;i--)
		{
		   x[i+1]=x[i];
		}
	
		x[location-1]= element;
	
		for (i=0;i<n+1;++i)
		{
			printf("%d ",x[i]);
	
		}
		return 0;
	}
	
	
	
	
