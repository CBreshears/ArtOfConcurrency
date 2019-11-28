#include <stdio.h>
#include <omp.h>

long long num_rects = 10000000;


int main(int argc, char* argv[])
{
	double mid, height, width, sum=0.0;
	int i;
	double area;
	width = 1./(double)num_rects;
#pragma omp parallel for private(mid, height) reduction(+:sum)
	for (i=0; i<num_rects; i++)
	{
		mid = (i + .5)*width;
		height = 4.0/(1.+ mid*mid);
		sum += height;
	}
	
	area = width * sum;

	printf("The value of PI is %15.12f\n",area);

	return 0;
}