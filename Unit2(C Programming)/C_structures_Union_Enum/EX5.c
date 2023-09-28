#include "stdio.h"
#include "stdlib.h"


#define PI 3.1415
#define AREA(r) (PI*(r)*(r))

int main(){
	int radius;
	float area;

	printf("Enter the radius: ");
	fflush(stdout);
	scanf("%d",&radius);

	area = AREA(radius);
	printf("Area = %.2f ",area);
	fflush(stdout);

	return 0;
}






