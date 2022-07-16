#include "stdio.h"
#include "stdlib.h"

void main()
{
	char x;
	printf("Enter a character: ");
	fflush(stdout); fflush(stdin);
	scanf("%c", &x);
	if ((x >= 'a' && 'z' >= x) ||(x >= 'A' && '	Z' >= x)){
		printf("%c is an alphabet: ", x);

	}
	else {
		printf("%c is not an alphabet: ", x);

	}


}




