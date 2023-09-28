#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int power(int i, int j)
{
	if (j!=0)
		return (i*power(i,j-1));
	else
		return 1;

}

int main()
{
	int i ,j;
	printf("Please enter base number:" );
	fflush(stdout);
	scanf("%d ", &i);

	printf("Please enter power number:(positive integer)" );
	fflush(stdout);
	scanf("%d ", &j);

	if (j==0) printf("%d^%d = 0",i,j);

	printf("%d^%d = %d",i,j,power(i,j));

	return 0;
}






