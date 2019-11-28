// Radixsort.cpp : Serial version of Radix Exchange sort algorithm.  
//
#include <windows.h>
#include <stdio.h>
#include "TSqueue.h"

#define N 100
// mbits is the number of bits from the key to be sorted upon for each pass
// M is 2^mbits, the values that can be represented with 2^mbits bits


long tCount = 0; // each element to be sorted will eventually be a single, unique-keyed element in partition
                 //                                           or within a partition of equal keys after all bit positions have been considered; 
                 // thus, will finish with value of N

int bits(int key, int bitPos, int numBits)
// return the numerical value of the number of bits (numBits) from the bitPos position within the key 
{
	int i,j,mask = 1;
	for (i = 1; i < numBits; i++) mask = mask * 2 + 1;
	mask = mask << bitPos;
	j = key & mask;
	j = j >> bitPos;
	return j;
}

int Partition(int *A, int p, int r, int bPos)
{
	int k = p-1;
	int l = r+1;
	int t;

		do k++; while ((k < r) && (bits(A[k],bPos,1) == 0));
		do l--; while ((l > p) && (bits(A[l],bPos,1) == 1));

		while (k < l) {
			t = A[k];  A[k] = A[l];  A[l] = t;
			do k++; while (bits(A[k],bPos,1) == 0);
			do l--; while (bits(A[l],bPos,1) == 1);
		}
		return l;
}

int RadixExchangeSort(int *A, int p, int r, int b)
// b is the number of bits in a key
{

	int q = 0;
	qParams *d=NULL, *d1, *d2;
	int bPos = b;

	// initial partition to prime the queue
//	q = Partition(A, p, r, bPos);
// encapsulate the indices for the upper portion of the partition and enqueue
	d1 = new qParams;
	d1->lo = p;
	d1->hi = r;
	d1->bitPosition = bPos;
	enqueue(d1);

//	for (int j = 0; j < N; j++) printf("%2d ",A[j]);
//	printf(" < %d %d %d\n\n", p, q, r);

	while (notEmpty()) {
     dequeue((LPVOID *)&d);  //pull out next index pair, unless queue is empty
		p = d->lo;
		r = d->hi;
		bPos = d->bitPosition-1;
		free(d);
		if ((p < r) && (bPos >= 0))  // if there is one or more things to sort and more bits to process...
		{
			q = Partition(A, p, r, bPos);

// encapsulate the indices for the lower portion of the partition and enqueue
			d1 = new qParams;
			d1->lo = p;
			d1->hi = q;
			d1->bitPosition = bPos;
			enqueue(d1);

// encapsulate the indices for the upper portion of the partition and enqueue
			d2 = new qParams;
			d2->lo = q+1;
			d2->hi = r;
			d2->bitPosition = bPos;
			enqueue(d2);
//	for (int j = 0; j < N; j++) printf("%2d ",A[j]);
//	printf(" < %d %d %d\n\n", p, q, r);
		}
//		else if (p == r) { //... else count the single element partition...
//			t = InterlockedIncrement(&tCount);
//	for (int j = 0; j < N; j++) printf("%2d ",A[j]);
//	printf(" < %d %d %d ==\n\n", p, q, r);
//		}
//		else {              //... otherwise count the parition with equal keys.
//			t = InterlockedExchangeAdd(&tCount, (long)(r-p+1));
//	for (int j = 0; j < N; j++) printf("%2d ",A[j]);
//	printf(" < %d %d %d bPos=%d\n\n", p, q, r, bPos);
//		}
	}
	return 0;
}



void init_data(int A[])
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
	int i, j;
    int *A = new int[N];

	init_data(A);
	initQueue();

	for ( i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\n\n");

	RadixExchangeSort(A, 0, N-1, sizeof(int)*8);
//	RadixExchangeSort(A, 0, N-1, 5);
	for ( j = 0; j < N; j++) printf("%3d ",A[j]);
	printf("\n\n");

	delete A;

	return 0;
}
