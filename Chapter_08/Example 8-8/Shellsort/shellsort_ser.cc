// Odd
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


void Shellsort(int P, int *A)
{
  int i, j, h, v;
  h = 1; while (h < P) h = 3*h + 1;
  while (h != 1) {
    h /= 3;
    for (i = h; i < P; i++) {
      v = A[i]; j = i;
      while (A[j-h] > v) {
		  A[j] = A[j-h]; 
		  j -= h;

        if (j <= h) break;
      }
      A[j] = v;
    }
  }
  InsertionSort(P,A);  // clean up
}

void Shellsort2(int P, int *A)
{
  int i, j, k, h, v;
  h = 1; while (h < N) h = 3*h + 1;
  h /= 3;
  while (h != 1) {
	  printf ("h = %d\n",h);
    for (k = 0; k < h; k++) {
      for (i = k; i < N; i+=h)  {
        v = A[i]; j = i;
      while (A[j-h] > v) {
		  A[j] = A[j-h]; 
		  j -= h;

        if (j <= h) break;
      }
       A[j] = v;
      }
    }  // for k
	h /= 3;
  }
  InsertionSort(N,A);  // clean up
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

	Shellsort(N,A);


	for ( j = 0; j < N; j++) printf("%3d ",A[j]);
	init_data();
	printf("\n\n\n\n");
	for ( i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\n\n");

	Shellsort2(N,A);

	for ( j = 0; j < N; j++) printf("%3d ",A[j]);
	return 0;
}