// OpenMP version of Shellsort

#include <windows.h>
#include <stdio.h>
#include <omp.h>

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


void Shellsort(int *A, int N)
{
  int k, h;
  h = 1; while (h < N) h = 3*h + 1;
  h /= 3;
#pragma omp parallel firstprivate(h)
 {
  while (h != 1) {
//	printf("h = %d\n",h);
#pragma omp for
	for (k = 0; k < h; k++) {
	  int i, j, v;
      for (i = k; i < N; i+=h)  {
        v = A[i]; j = i;
        while (j >= h && A[j-h] > v) {
          A[j] = A[j-h]; 
          j -= h;
        }
        A[j] = v;
      }
    }  // for k
    h /= 3;
  }  // end while
 }  // end parallel region
  InsertionSort(A, N);  // clean up
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

	Shellsort(A, NN);

	for ( j = 0; j < NN; j++) printf("%3d ",A[j]);

	return 0;
}