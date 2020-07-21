// OpenMP version of Prefix Scan (sum) algorithm

#include <windows.h>
#include <omp.h>
#include <stdio.h>

#define NN 2000


int X[NN];


void init_data()
{
	int i;
	for (i = 0; i < NN; i++)
		X[i] = i+1;
}

int main(int argc, char* argv[])
{	
	int sum = 0;

	init_data();
#pragma omp parallel for reduction(+:sum)
	for (int i = 0; i < NN; i++) 
		sum = sum + X[i];

	printf("The sum of array elements is %d\n", sum);
	return 0;
}