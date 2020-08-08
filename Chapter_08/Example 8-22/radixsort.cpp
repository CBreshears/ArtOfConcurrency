// Radixsort.cpp : Serial version of straight Radix sort algorithm.  
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pth_barrier.h"
#include "radixsort.h"

#define NN 2048
#define NUM_THREADS 4
// mbits is the number of bits from the key to be sorted upon for each pass
// M is 2^mbits, the values that can be represented with 2^mbits bits

#define mbits 2
#define M 4

int lCount[NUM_THREADS][M];
int gCount[M];
int fCount[M];

pth_barrier_t b1, b2;
int *A = new int[NN];               // temporary pointer 
int *tA = new int[NN];               // temporary pointer 

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


void *ParallelStraightRadixSort(void *par)
{
  tParams *lpar = (tParams *) par;
  int N = lpar->num;
  int b = lpar->keylength;
  int tNum = lpar->tid;

  int i, j, pass, tBits;
  int *tempPtr;
  int start, end, offset;

  start = ((float)N/NUM_THREADS) * tNum;
  end =   ((float)N/NUM_THREADS) *(tNum+1);
  if (tNum == NUM_THREADS-1) end = N;

//printf("S, e: %d %d\n", start, end);
//printf("b, tid: %d %d\n", b, tNum);

  for (pass = 0; pass < (b / mbits); pass++) {
    for (j = 0; j < M; j++) lCount[tNum][j] = 0;
    for (i = start; i < end; i++)
      lCount[tNum][bits(A[i],pass*mbits, mbits)]++;
//printf("%d lC: %d %d %d %d \n",tNum, lCount[tNum][0], lCount[tNum][1],lCount[tNum][2],lCount[tNum][3]);
    pth_barrier(&b1);
    if (tNum == 0) { // one thread computes sums
      // sum for each bit pattern from lCount totaled into gCount
      for (i = 0; i < M; i++) {
        gCount[i] = 0;
        for (j = 0; j < NUM_THREADS; j++)
          gCount[i] += lCount[j][i];
      }
//printf("%d gC: %d %d %d %d \n",tNum, gCount[0], gCount[1],gCount[2],gCount[3]);
      // exclusive prefix of gCount into fCount
      fCount[1] = gCount[0]-1;
      for (i = 2; i < M; i++) 
        fCount[i] = fCount[i-1] + gCount[i-1];
      fCount[0] = -1;
//printf("%d fC: %d %d %d %d \n",tNum, fCount[0], fCount[1],fCount[2],fCount[3]);
      // prefix scan for each bit pattern from fCount through lCount
      for (i = 0; i < M; i++) {
        lCount[0][i] += fCount[i];
        for (j = 1; j < NUM_THREADS; j++)
          lCount[j][i] += lCount[j-1][i];
      }
    }
    pth_barrier(&b2);  // other threads wait for all sum computations
//printf("%d lC: %d %d %d %d \n",tNum, lCount[tNum][0], lCount[tNum][1],lCount[tNum][2],lCount[tNum][3]);

    for (i = end-1; i >= start; i--) {
      tBits = bits(A[i], pass*mbits, mbits);
      tA[lCount[tNum][tBits]] = A[i];
      lCount[tNum][tBits]--;
    }
    pth_barrier(&b1);
    // swap pointers to swap arrays for next pass
    if (tNum == 0) { tempPtr = tA; tA = A; A = tempPtr; }
    pth_barrier(&b2);
  }
} 
void init_data(int A[])
{
  int i, x, y;
  for (i = 0; i < NN; i++) A[i] = i;
  for (i = 0; i < NN; i++) {
    x = rand() % NN; 
    y = A[x]; A[x] = A[i]; A[i] = y;
  }
}

int main(int argc, char* argv[])
{  
  int i, j;
  pthread_t tHandles[NUM_THREADS];

  init_data(A);
  pth_barrier_init(&b1, NUM_THREADS);
  pth_barrier_init(&b2, NUM_THREADS);

  for ( i = 0; i < NN; i++) printf("%3d ",A[i]);
  printf("\n\n");

  for (i = 0; i < NUM_THREADS; i++) {
    tParams *par = new(tParams);
    par->num = NN;
    par->keylength = sizeof(int)*8;
    par->tid = i;
    pthread_create(&tHandles[i], NULL, ParallelStraightRadixSort, (void*)par);
  }

  for (i = 0; i < NUM_THREADS; i++)
    pthread_join(tHandles[i], NULL);

  for ( j = 0; j < NN; j++) printf("%3d ",A[j]);
  printf("\n\n");

  free(A);
  free(tA);
  return 0;
}
