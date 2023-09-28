#include "stdio.h"
#include "stdlib.h"

int main()
{
	char s[100], ch;
	int i, length=0;

	printf("Enter a string: ");
	fflush(stdout); fflush(stdin);
	gets(s);


	for(i=0; s[i]!='\0'; i++)
	{
			length ++;

	}

	printf("length of string is %d" , length);
	fflush(stdout); fflush(stdin);


	return 0;
}




