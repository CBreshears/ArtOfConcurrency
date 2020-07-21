/**
 * @file pi_pth.cc
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2020 Clay Breshears (clay.breshears@gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION Pthreads implementation of numerical integration code 
 *
 * @section CITATION
 *          Example 5-3 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/

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

   for (int i = myNum; i < NUM; i += NUM_THREADS) {
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

   for (int j = 0; j < NUM_THREADS; ++j) {
      pthread_join(tHandles[j], NULL);
   }

   pthread_mutex_destroy(&gLock);
   printf("The value of PI is %15.12f\n",gArea);
}
