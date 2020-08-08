// ParallelRadixsort.cpp : Second version of straight Radix sort algorithm.  
//
#include <windows.h>
#include <stdio.h>

#define NN 100
// mbits is the number of bits from the key to be sorted upon for each pass
// M is 2^mbits, the values that can be represented with 2^mbits bits

//int count[NUM_THREADS];

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

void SerialStraightRadixSort(int *A, int N, int b)
// b is the number of bits in a key, b must be a divisor of mbits
{
	#define mbits 4
	#define M 16

	int i, j, pass;
	int offset, rank;
	int count;
	int *tA = new int[N];
	int *tempPtr; 

	for (pass = 0; pass < (b / mbits); pass++) {
		offset = -1; //for 0-base index
		for (j = 0; j < M; j++) {
			count = 0;
			for (i = 0; i < N; i++) {
				if (bits(A[i],pass*mbits, mbits) == j) count++;
			}
			rank = offset + count;
			for (i = N-1; i >= 0; i--) {
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


void init_data(int A[])
{
	int i,j,t;
	for (i = 0; i < NN; i++)
		A[i] = i;
	for (i = 0; i < NN; i++) {
		j = rand() % NN;
		t = A[i]; 
		A[i] = A[j];
		A[j] = t;
	}
}

int main(int argc, char* argv[])
{	
	int j;
    int *A = new int[NN];

	init_data(A);
	for ( j = 0; j < NN; j++) printf("%3d ",A[j]);
	printf("\n\n");
	SerialStraightRadixSort(A, NN, sizeof(int)*8);
	for ( j = 0; j < NN; j++) printf("%3d ",A[j]);
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
	return 0;
}
