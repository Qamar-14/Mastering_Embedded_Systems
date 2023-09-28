#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int main()
{
	char s[100], str[100];
	int i, length;

	printf("Enter the string: ");
	fflush(stdout); fflush(stdin);
	gets(s);

	length = strlen(s) -1;
	for(i=0; i<= strlen(s); i++)
	{
		str[i]=s[length -i];
	}

	printf("The reverse string: %s " , str);
	fflush(stdout); fflush(stdin);


	return 0;
}




