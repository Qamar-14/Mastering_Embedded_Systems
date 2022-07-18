#include "stdio.h"
#include "stdlib.h"

int main()
{
	char s[100], ch;
	int i, frequency=0;

	printf("Enter a string: ");
	fflush(stdout); fflush(stdin);
	gets(s);

	printf("Enter a character to find frequency: ");
	fflush(stdout); fflush(stdin);
	scanf("%c ", &ch);

	for(i=0; s[i]!='\0'; i++)
	{
		if(ch==s[i])
		{
			frequency ++;
		}
	}

	printf("Frequency of %c is %d", ch , frequency);
	fflush(stdout); fflush(stdin);


	return 0;
}




