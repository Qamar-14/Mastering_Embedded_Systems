#include "stdio.h"

struct Employee {
	char *Name;
	int ID;
};

int main() {

	struct Employee emp1={"Alex", 1002},emp2={"Youssef", 2001},emp3={"Qamar",9016};
	struct Employee(*arr[])={&emp1, &emp2, &emp3};
	struct Employee(*(*pt)[3])= &arr;

	printf("Employee Name : %s ", (**(*pt)).Name);
	printf("\nEmployee ID : %d ", (*(*pt))->ID);

	return 0;

}



