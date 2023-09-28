#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct student{

	char Name[40];
	int rollNumber;
	float marks;

};


int main(){
	struct student s[10];
	int i;

	printf("Enter information of students:\n");
	for (i=0;i<10;i++)
	{
		s[i].rollNumber=i+1;
		printf("For roll number %d\n", s[i].rollNumber);
		fflush(stdout);

		printf("Enter Name:");
		fflush(stdout);
		scanf("%s", &s[i].Name);

		printf("Enter marks: ");
		fflush(stdout);
		scanf("%f", &s[i].marks);
	}

	printf("Displaying information for students:\n");
	fflush(stdout);
	for (i=0;i<10;i++){
	printf("Information for roll number %d:\nName: %s\nMarks: %.2f \n",s[i].rollNumber, s[i].Name,s[i].marks);
	fflush(stdout);
	}
	return 0;
}






