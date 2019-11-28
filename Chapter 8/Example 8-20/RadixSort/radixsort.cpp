// Radixsort.cpp : Serial version of straight Radix sort algorithm.  
//
#include <windows.h>
#include <stdio.h>

#define NN 100
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

void StraightRadixSort(int *A, int N, int b)
// b is the number of bits in a key, b must be a divisor of mbits
{
	#define mbits 4
	#define M 16

	int i, j, pass, tBits;
	int count[M];
	int *tA = new int[N];
	int *tempPtr; 

	for (pass = 0; pass < (b / mbits); pass++) {
		for (j = 0; j < M; j++) count[j] = 0;
		for (i = 0; i < N; i++) {
			count[bits(A[i],pass*mbits, mbits)]++;
		}
		count[0]--;
		for (j = 1; j < M; j++) count[j] += count[j-1];  // prefix sum on counts
		for (i = N-1; i >= 0; i--) {
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
	int i, j;
    int *A = new int[NN];

	init_data(A);

	for ( i = 0; i < NN; i++) printf("%3d ",A[i]);
	printf("\n\n");

	StraightRadixSort(A, NN, sizeof(int)*8);
	for ( j = 0; j < NN; j++) printf("%3d ",A[j]);
	printf("\n\n");

	delete A;
	return 0;
}
