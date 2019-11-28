#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "pth_barrier.h"

#define NUM_THREADS 8
#define NUM 2000

int N=NUM;  // number of elements in array X
int X[NUM];
//int N;  // number of elements in array X
//int *X;
int gSum[NUM_THREADS];  // global storage for partial results

pth_barrier_t B;

void *SumByReduction (void *pArg)
{
  int tNum = *((int *) pArg);
  int lSum = 0;
  int start, end, i;

  start = ((float)N / NUM_THREADS) * tNum;
  end =   ((float)N / NUM_THREADS) *(tNum+1);
  if (tNum == (NUM_THREADS-1)) end = N;
  for (i = start; i < end; i++)
    lSum += X[i];
  gSum[tNum] = lSum;

  pth_barrier(&B);
  int p2 = 2;
  for (i = 1; i <= NUM_THREADS; i *= 2) {
    if ((tNum % p2) == 0) 
      if (tNum+i < NUM_THREADS) gSum[tNum] += gSum[tNum+i];
    p2 *= 2;
    pth_barrier(&B);
  }
  free(pArg);
}

void InitializeArray(int *S, int *N)
{
  for (int i = 0; i < NUM; i++){
    S[i] = i+1;
  }
}

int main(int argc, char* argv[])
{
  int j, sum = 0;
  pthread_t tHandles[NUM_THREADS];

  InitializeArray(X,&N);  // get values into A array; not shown
  pth_barrier_init(&B, NUM_THREADS);

  for (j = 0; j < NUM_THREADS; j++) {
    int *threadNum = new(int);
    *threadNum = j;
    pthread_create(&tHandles[j], NULL, SumByReduction, (void *)threadNum);
  }
// just wait for thread  with id=0 to terminate; others will follow
  pthread_join(tHandles[0], NULL);
  printf("The sum of array elements is %d\n", gSum[0]);
  return 0;
}
