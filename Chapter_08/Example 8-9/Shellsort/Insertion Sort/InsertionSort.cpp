
#include <windows.h>
#include <stdio.h>

#define N 100

int A[N];

void InsertionSort(int P, int *A)
{
	int i, j, v;
  for (i = 1; i < P; i++) {
    v = A[i]; 
    j = i;
    while (A[j-1] > v) {
		A[j] = A[j-1]; j--;
      if (j <= 0) break;
    }
    A[j] = v;
  }
}


void init_data()
{
	int i, x, y, t;
	for (i = 0; i < N; i++)
		A[i] = i;
	for (i = 0; i < N; i++){
		x = rand() % N;
			y = rand() % N;
			t = A[x]; A[x] = A[y]; A[y] = t;
	}
}


int main(int argc, char* argv[])
{	
	int i, j;

	init_data();

	for ( i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\n\n");

	InsertionSort(N,A);

	for ( j = 0; j < N; j++) printf("%3d ",A[j]);
	return 0;
}