#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void reverse()
{
	char c;
    scanf("%c ", &c);
	fflush(stdout);

	if (c!= '\n')
	{
		reverse();
		printf("%c ", c);
		fflush(stdout);


	}
}

int main()
{
	printf("Please enter a sentence:" );
	fflush(stdout);
	reverse();

	return 0;
}






