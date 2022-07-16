#include "stdio.h"
#include "stdlib.h"

void main()
{
	int i;
	char x ;
	//char vowels[]={'A','a','I','i','E','e','o','O','U','u'};

	printf("Enter an alphabet: ");
	fflush(stdout); fflush(stdin);
	scanf("%c", &x);
	if (x=='A'||x== 'a'|| x== 'I'|| x== 'i'|| x== 'E'|| x== 'e'|| x== 'o'|| x=='O'|| x=='U'|| x== 'u')
	{
		printf("%c is a vowel",x);
	}
	else
	{
		printf("%c is a consonant",x);
	}

}
