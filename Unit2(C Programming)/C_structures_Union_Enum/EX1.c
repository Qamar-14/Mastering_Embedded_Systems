#include "stdio.h"
#include "stdlib.h"
#include "string.h"



int main()
{
	struct student{

		char Name[40];
		int rollNumber;
		float marks;

	}s;
	printf("Enter information of students:\n");
	printf("Enter Name:");
	fflush(stdout);
	scanf("%s", &s.Name);

	printf("Enter roll number: ");
	fflush(stdout);
	scanf("%d",&s.rollNumber);


	printf("Enter marks: ");
	fflush(stdout);
	scanf("%f", &s.marks);


	printf("Displaying information:\n");
	fflush(stdout);
	printf("Name: %s \nRoll Number: %d \nMarks: %.2f \n",s.Name ,s.rollNumber ,s.marks);
	fflush(stdout);

	return 0;
}






