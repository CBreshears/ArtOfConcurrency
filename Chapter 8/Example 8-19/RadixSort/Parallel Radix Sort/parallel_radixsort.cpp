// ParallelRadixsort.cpp : Parallel version of straight Radix sort algorithm.  
//
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include "parallel_radixsort.h"


#define NUM_THREADS 2
#define N 200
// mbits is the number of bits from the key to be sorted upon for each pass
// M is 2^mbits, the values that can be represented with 2^mbits bits

int count[NUM_THREADS];

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

void SerialStraightRadixSort(int *A, int num, int b)
// b is the number of bits in a key, b must be a divisor of mbits
{
	#define mbits 4
	#define M 16

	int i, j, pass;
	int offset, rank;
	int count;
	int *tA = new int[num];
	int *tempPtr; 

	for (pass = 0; pass < (b / mbits); pass++) {
		offset = -1; //for 0-base index
		for (j = 0; j < M; j++) {
			count = 0;
			for (i = 0; i < num; i++) {
				if (bits(A[i],pass*mbits, mbits) == j) count++;
			}
			rank = offset + count;
			for (i = num-1; i >= 0; i--) {
				if (bits(A[i],pass*mbits, mbits) == j) 
					tA[rank--] = A[i];
			}
			offset += count;
		}
/*
		printf("pass = %d\n A: ",pass);
		for ( i = 0; i < N; i++) printf("%3d ",A[i]);
		printf("\ntA: ");
		for ( i = 0; i < N; i++) printf("%3d ",tA[i]);
		printf("\n\n");
*/

		// swap pointers to swap arrays to sort in next pass
		tempPtr = tA; tA = A; A = tempPtr;
	}
	free(tA);
}

void ParallelStraightRadixSort(void *par)

{
	#define mbits 4
	#define M 16

	tParams *lpar = (tParams *) par;
	int *A = lpar->A;
	int num = lpar->num;
	int b = lpar->keylength;
	int myid = lpar->tid;

	int i, j, pass, tBits;
	int count[M];
	int *tA = new int[num];
	int *tempPtr;
	int start, end, offset;

	start = (int)((float)num/NUM_THREADS) * myid;
	end =   (int)((float)num/NUM_THREADS) *(myid+1);
	if (myid == NUM_THREADS-1) end = num;

	for (pass = 0; pass < (b / mbits); pass++) {
		offset = 0;
		for (i = 0; i < M; i++) {
			count[myid] = 0;
			for (j = start; j < end; j++)
				if (bits(A[j],pass*mbits, mbits) == i) count[myid]++;
		}

		count[myid] = 0;
		for (i = 0; i < num; i++) {
			count[bits(A[i],pass*mbits, mbits)]++;
		}
		count[0]--;
		for (j = 1; j < M; j++) count[j] += count[j-1];  // prefix sum on counts
		for (i = num-1; i >= 0; i--) {
			tBits = bits(A[i], pass*mbits, mbits);
			tA[count[tBits]] = A[i];
			count[tBits]--;
		}
/*
		printf("pass = %d\n A: ",pass);
		for ( i = 0; i < N; i++) printf("%3d ",A[i]);
		printf("\ntA: ");
		for ( i = 0; i < N; i++) printf("%3d ",tA[i]);
		printf("\n\n");
*/

		// swap pointers to swap arrays to sort in next pass
		tempPtr = tA; tA = A; A = tempPtr;
	}
	free(tA);
}

void init_data(int A[], int B[])
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
	for (i = 0; i < N; i++)
		B[i] = A[i]; 
}

int main(int argc, char* argv[])
{	
	int j;
    int *A = new int[N];
	int *B = new int[N];

	init_data(A, B);
	for ( j = 0; j < N; j++) printf("%3d ",A[j]);
	printf("\n\n");
	SerialStraightRadixSort(A, N, sizeof(int)*8);
	for ( j = 0; j < N; j++) printf("%3d ",A[j]);
	printf("\n\n");

	/*

	for ( i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\n\n");

	for (i = 0; i < NUM_THREADS; i++) {
		tParams *p = new tParams;
		p->B;
		p->num = N;
		p->keylength = sizeof(int)*8;
		p->tid = i; 
		hThreads[i] = (HANDLE) _beginthreadex(NULL, 0, ParallelStraightRadixSort, (void *)p, 0, NULL);
	}
	WaitForMultipleObjects(NUM_THREADS, hThreads, TRUE, INFINTE);

	for ( j = 0; j < N; j++) printf("%3d ",B[j]);
	printf("\n\n");
/*
//	RadixExchangeSort(A, 0, N-1, sizeof(int)*8);
//	RadixExchangeSort(A, 0, N-1, 5);

	for ( j = 0; j < N; j++) printf("%3d ",A[j]);
	printf("\n\n");
	//printf("tCount = %d\n",tCount);
*/

	delete A;
	delete B;
	return 0;
}
