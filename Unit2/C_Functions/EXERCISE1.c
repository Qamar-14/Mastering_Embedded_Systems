#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int checkPrime(int number)
{
  int count = 0;

  for(int i=2; i<=number/2; i++)
  {
     if(number%i == 0)
     {
       count=1;
       break;
     }
  }

  if(number == 1) count = 1;

  return count;
}

int main()
{
	int i,j;
	printf("Enter two numbers(intervals):" );
	fflush(stdout);
	scanf("%d \n %d",&i, &j);
	 printf("Prime numbers between %d and %d are: ", i, j);
	for( int x=i; x< j+1; x++){
		if (checkPrime(x)==0)
		printf("%d ", x);
	  }

}






