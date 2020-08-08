// Quicksort Iterative.cpp : Iterative version of Quicksort algorithm using a thread-safe queue data structure to 
//                             simulate recursive nature of the original algorithm.  
//
#include <windows.h>
#include <stdio.h>
#include "TSQueue.h"

#define N 100

int A[N];
long tCount = 0; // each element to be sorted will eventually be the pivot or single element in partition; 
                 //                   thus, will finish with value of N

int Partition (int p, int r)
{
	int x = A[p];
	int k = p;
	int l = r+1;
	int t;
	while (1)
	{
		do 
		  k++;
		while ((A[k] <= x) && (k < r));
		do 
		  l--;
		while (A[l] > x);

		while (k < l) {
			t = A[k];  A[k] = A[l];  A[l] = t;
			do k++; while (A[k] <= x);
			do l--; while (A[l] > x);
		}
		t = A[p];  A[p] = A[l];  A[l] = t;
		return l;
	}
}

DWORD WINAPI QuickSort(LPVOID pArg)
{
	int p;
	int r;
	int q;
	qParams *d=NULL, *d1, *d2;
	long t;

	while (1) {
		if (dequeue((LPVOID *)&d)) break;  //pull out next index pair, unless queue is empty
		p = d->lo;
		r = d->hi;
		free(d);
		if (p < r)  // if there is one or more things to sort...
		{
			q = Partition(p, r);
			t = InterlockedIncrement(&tCount);

// encapsulate the indices for the lower portion of the partition and enqueue
			d1 = (qParams *) malloc(sizeof(qParams));
			d1->lo = p;
			d1->hi = q-1;
			enqueue(d1);

// encapsulate the indices for the upper portion of the partition and enqueue
			d2 = (qParams *) malloc(sizeof(qParams));
			d2->lo = q+1;
			d2->hi = r;
			enqueue(d2);
		}
		else if (p == r)  //... else count the single element partition
			t = InterlockedIncrement(&tCount);
	}
	return 0;
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
	int q;
	int i;
	qParams *e1, *e2;

	init_data();
	initQueue();

	for (i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\n\n");

	// Initial partition of data and enqueueing of first two index pairs before calling QuickSort
	q = Partition(0, N-1);
	InterlockedIncrement(&tCount);

	e1 = (qParams *) malloc(sizeof(qParams)); e1->lo = 0; e1->hi = q-1;
	enqueue((LPVOID)e1);
	e2 = (qParams *) malloc(sizeof(qParams)); e2->lo = q+1; e2->hi = N-1;
	enqueue((LPVOID)e2);

	QuickSort(NULL);

	for ( i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\nTCOUNT = %d\n", tCount);
	return 0;
}