// Bubblesrot.cpp : serial version of Bubblesort algorithm.  
//
#include <windows.h>
#include <process.h>
#include <stdio.h>

#define NN 100

int A[NN];

void BubbleSort(int *A, int N)
{
  int i, j;
  int temp;
  for (i = N-1; i > 0; i--) {
    for (j = 0; j < i; j++) {
      if (A[j] > A[j+1]) {
        temp = A[j]; A[j] = A[j+1]; A[j+1] = temp;
      }
    }
  }
}

void init_data()
{
	int i, x, y;
	for (i = 0; i < NN; i++)
		A[i] = i;
	for (i = 0; i < NN; i++) {
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

 	BubbleSort(A,NN);

	for ( j = 0; j < NN; j++) printf("%3d ",A[j]);
	return 0;
}
