#include "stdio.h"


int main() {
	char str[50];
	int i;
	char *ptr = str;

	printf("Input a string:\n");
	fflush(stdout);
	scanf("%s",str);

	for (i =0; i<strlen(str) ; i++){
		ptr++;
	}
	fflush(stdout);
	printf("Reverse of the string is:\n");
	fflush(stdout);

	for (i =0; i<strlen(str) ; i++){
		ptr--;
		printf("%c",*ptr);
	}



	return 0;
}



