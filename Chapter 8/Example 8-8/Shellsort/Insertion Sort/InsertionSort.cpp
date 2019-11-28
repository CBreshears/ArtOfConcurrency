
#include <windows.h>
#include <stdio.h>

#define NN 100

int A[NN];

void InsertionSort(int *A, int N)
{
  int i, j, v;
  for (i = 1; i < N; i++) {
    v = A[i]; 
    j = i;
    while (A[j-1] > v) {
      A[j] = A[j-1]; 
      j--;
      if (j <= 0) break;
    }
    A[j] = v;
  }
}


void init_data()
{
	int i, x, y;
	for (i = 0; i < NN; i++)
		A[i] = i;
	for (i = 0; i < NN; i++){
		x = rand() % NN;
		y = A[x]; A[x] = A[i]; A[i] = y;
	}
}


int main(int argc, char* argv[])
{	
	int i, j;

	init_data();

	for ( i = 0; i < NN; i++) printf("%3d ",A[i]);
	printf("\n\n");

	InsertionSort(A, NN);

	for ( j = 0; j < NN; j++) printf("%3d ",A[j]);
	return 0;
}