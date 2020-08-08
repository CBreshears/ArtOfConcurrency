// Quicksort recursive.cpp : Traditional recursive version of Quicksort algorithm.  

//
#include <windows.h>
#include <stdio.h>

#define N 100

int A[N];
long tCount = 0;

int Partition (int p, int r)
{	int x = A[p];
	int k = p;
	int l = r+1;
	int t;

	do k++; while ((A[k] <= x) && (k < r));
	do l--; while (A[l] > x);

	while (k < l) {
		t = A[k];  A[k] = A[l];  A[l] = t;
		do k++; while (A[k] <= x);
		do l--; while (A[l] > x);
	}
	t = A[p];  A[p] = A[l];  A[l] = t;
	return l;
}

void QuickSort(int p, int r)
{
	int q;

	if (p < r) {
		q = Partition(p, r);
		InterlockedIncrement(&tCount);
		QuickSort (p, q-1); 
		QuickSort (q+1, r);
	}
	else if (p == r) InterlockedIncrement(&tCount);
}

void init_data()
{
	int i,j,t;
	for (i = 0; i < N; i++)
		A[i] = i;
	for (i = 0; i < N; i++) {
		j = rand() % N;
		t = A[i]; 
		A[i] = A[j];
		A[j] = t;
	}
}

int main(int argc, char* argv[])
{
	init_data();
	for (int i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\n\n");
	QuickSort(0, N-1);
	for (int j = 0; j < N; j++) printf("%3d ",A[j]);
	printf("\nTCOUNT = %d\n", tCount);
	return 0;
}
