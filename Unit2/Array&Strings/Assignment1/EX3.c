#include "stdio.h"
#include "stdlib.h"

int main()
{
	int i, j, n, k;
	float x[10][10];


	printf("Enter rows and columns of matrix: \n");
	fflush(stdout); fflush(stdin);

	scanf("%d \r\n %d", &n,&k);

	if ((n*k)>100 || n<=0 || k<=0)
	{
		printf("Error, Number out of range. Please enter the number of rows and columns again");
		scanf("%d \r\n %d", &n,&k);
	}
	else
	{
		printf("Enter elements of matrix: \r\n ");

		for (i=0;i<n;++i)
		{
			for (j=0;j<k;++j)
			{
				printf("Enter elements %d%d: ", i+1, j+1);
				fflush(stdout); fflush(stdin);
				scanf("%f ", &x[i][j]);
				fflush(stdout); fflush(stdin);
			}
		}
	}
	printf("Entered matrix: \n ");

	for (i=0;i<n;++i)
		{
			for (j=0;j<k;++j)
			{
				printf("%.2f\t ",x[i][j]);
				if (j==(k-1))
					printf("\n");
			}

		}
	printf("Transpose of matrix: \r\n");

		for (i=0;i<k;++i)
			{
				for (j=0;j<n;++j)
				{
					printf("%.2f\t ",x[j][i]);
					if (j==(n-1))
						printf("\n");
				}

			}



	return 0;
}




