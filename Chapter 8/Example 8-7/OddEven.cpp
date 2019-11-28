// Odd
#include <windows.h>
#include <stdio.h>

#define NN 100

int A[NN];

void OESort(int *A, int N)
{
	int exch0, exch1 = 1, trips = 0, i;

	while (exch1) {
		exch0 = 0;
		exch1 = 0;
#pragma omp parallel 
		{int temp;
#pragma omp  for  
		for (i = 0; i < N-1; i += 2) {
			if (A[i] > A[i+1]) {
				temp = A[i]; A[i] = A[i+1]; A[i+1] = temp;
				exch0 = 1;
			}
		}
		if (exch0 || !trips) {
#pragma omp  for  
			for (i = 1; i < N-1; i += 2) {
				if (A[i] > A[i+1]) {
					temp = A[i]; A[i] = A[i+1]; A[i+1] = temp;
					exch1 = 1;
				}
			}
		}
		}
		trips = 1;
	}
}

void init_data()
{
	int i,j,t;
	for (i = 0; i < NN; i++)
		A[i] = i;
	for (i = 0; i < NN; i++) {
		j = rand() % NN;
		t = A[i]; 
		A[i] = A[j];
		A[j] = t;
	}
}

int main(int argc, char* argv[])
{	
	int i, j;

	init_data();

	for ( i = 0; i < NN; i++) printf("%3d ",A[i]);
	printf("\n\n");

	OESort(A, NN);

	for ( j = 0; j < NN; j++) printf("%3d ",A[j]);
	printf("\n\n");
	
	return 0;
}