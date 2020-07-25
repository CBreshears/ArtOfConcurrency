/**
 * @file prefixscan_win.cpp
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
 * @section DESCRIPTION Prefix scan code to sum array elements using Windows
 *                      threads
 *                     
 * @section CITATION
 *          Example 6-8 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/
#include <windows.h>
#include <process.h>
#include <stdio.h>

#define NUM_THREADS 4
#define N 100

//int A[16] ={3,5,2,5,7,9,-4,6,7,-3,1,7,6,8,-1,2};
int A[N];
int inTotals[NUM_THREADS], outTotals[NUM_THREADS];
HANDLE doneStep1[NUM_THREADS];
HANDLE doneStep2;

unsigned __stdcall prefixScan(LPVOID pArg)
{
   int myid = *((int *) pArg);
   int start, end, i;
   int lPrefixTotal;

   free(pArg);
   start = (N / NUM_THREADS) * myid;
   end = (N / NUM_THREADS) * (myid + 1);
   if (myid == (NUM_THREADS-1)) end = N;

   // Step 1
   for (i = start+1; i < end; ++i) 
      A[i] = A[i-1] + A[i];
   inTotals[myid] = A[end-1];

   SetEvent(doneStep1[myid]); //signal completion of Step 1

   WaitForSingleObject(doneStep2, INFINITE); // wait for completion of Step 2

   // Step 3
   lPrefixTotal = outTotals[myid];   
   printf("id: %d  lPT = %d\n",myid, lPrefixTotal);
   for (i = start; i < end; ++i) 
      A[i] = lPrefixTotal + A[i];

   return 0;
}

void init_data()
{
   int i;
   for (i = 0; i < N; ++i)
      A[i] = rand() % N;
}

int main(int argc, char* argv[])
{   
   int i, j;
   HANDLE tH[NUM_THREADS];

   init_data();

// Create manual reset event initially unsignaled
   for (i = 0; i < NUM_THREADS; ++i) 
      doneStep1[i] = CreateEvent(NULL, TRUE, FALSE, NULL); 

// manual reset event initially unsignaled
   doneStep2 = CreateEvent(NULL, TRUE, FALSE, NULL); 

   for ( i = 0; i < N; ++i) printf("%3d ",A[i]);
   printf("\n\n");

   for (i = 0; i < NUM_THREADS; ++i) {
      int *tnum = new int;
      *tnum = i;
      tH[i] = (HANDLE) _beginthreadex(NULL, 0, prefixScan, (LPVOID) tnum, 0, NULL);
   }

// wait for Step 1 completion
   WaitForMultipleObjects(NUM_THREADS, doneStep1, TRUE, INFINITE); 

//   for ( j = 0; j < NUM_THREADS; j++) printf("%3d ",inTotals[j]);
//   printf("\n");

   // Step 2
   outTotals[0] = 0;
   for (j = 1; j < NUM_THREADS; j++) {
      outTotals[j] = outTotals[j-1] + inTotals[j-1];
   }

//    for ( j = 0; j < NUM_THREADS; j++) printf("%3d ",outTotals[j]);
//   printf("\n");

   SetEvent(doneStep2);  //signal completion of Step 2

// wait for completion of Step 3
   WaitForMultipleObjects(NUM_THREADS, tH, TRUE, INFINITE); 

   for ( j = 0; j < N; j++) printf("%3d ",A[j]);
   printf("\n");
   return 0;
}
