#include <stdio.h>
#include <pthread.h>

#define NUM 1000000000
#define NUM_THREADS 4

double gArea = 0.0;
pthread_mutex_t gLock;

void *threadFunction(void *pArg)
{
  int myNum = *((int *)pArg);
  double partialHeight = 0.0, lWidth = 1.0 / NUM, x;

  for (int i = myNum; i < NUM; i += NUM_THREADS)
  {
    x = (i + 0.5f) / NUM;
    partialHeight += 4.0f / (1.0f + x*x);
  }

  pthread_mutex_lock(&gLock);
   gArea += partialHeight * lWidth;  
  pthread_mutex_unlock(&gLock);
}

int main()
{
  pthread_t tHandles[NUM_THREADS];
  int tNum[NUM_THREADS];

  pthread_mutex_init(&gLock, NULL);
  for (int i = 0; i < NUM_THREADS; ++i) {
    tNum[i] = i;
    pthread_create(&tHandles[i], NULL, threadFunction, (void *)&tNum[i]); 
  }

  for ( int j=0; j<NUM_THREADS; ++j ) {
    pthread_join(tHandles[j], NULL);
  }

  pthread_mutex_destroy(&gLock);
  printf("Computed value of Pi: %f\n", gArea);
}
