#include "stdio.h"


int main() {
	char abc[26];
	int i;
	char *ptr;
	ptr = abc;

	for (i =0; i<26 ; i++){
		*ptr = 'A' + i;
		ptr++;
	}
	printf("The alphabets are:\n");
	ptr = abc;
	for (i =0; i<26 ; i++){
			printf("%c\t",*ptr);
			ptr++;
		}


	return 0;
}



