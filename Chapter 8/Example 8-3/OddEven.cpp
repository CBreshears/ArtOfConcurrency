// Odd
#include <windows.h>
#include <stdio.h>

#define N 100

int A[N];

void OESort(int NN, int *A)
{
	int exch = 1, start = 0, i;
	int temp;

	while (exch || start) {
		exch = 0;
//#pragma omp parallel for private(temp)
		for (i = start; i < NN-1; i+=2) {
			if (A[i] > A[i+1]) {
				temp = A[i]; A[i] = A[i+1]; A[i+1] = temp;
				exch = 1;
			}
		}
		if (start == 0) start = 1;
		else start = 0;
	}
}

void init_data()
{
	int i;
	for (i = 0; i < N/2; i++)
		A[i] = i + N/2;
	//	A[i] = rand() % N;
	for (i = N/2; i < N; i++)
		A[i] = i - N/2;

}

int main(int argc, char* argv[])
{	
	int i, j;

	init_data();

	for ( i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\n\n");

	OESort(N,A);

	for ( j = 0; j < N; j++) printf("%3d ",A[j]);
	return 0;
}