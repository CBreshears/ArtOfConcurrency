/**
 * @file oddeven_final.cc
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
 * @section DESCRIPTION OpenMP implementation of final implementation of 
 *                      Odd-Even Transposition sort
 * @section CITATION
 *          Example 8-7 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/
#include <stdlib.h>
#include <stdio.h>

#define NN 100

int A[NN];

void OESort(int *A, int N)
{
   int exch0, exch1 = 1, trips = 0, i;

   while (exch1) {
      exch0 = 0;
      exch1 = 0;
#pragma omp parallel 
      {int temp;
#pragma omp  for  
      for (i = 0; i < N-1; i += 2) {
         if (A[i] > A[i+1]) {
            temp = A[i]; A[i] = A[i+1]; A[i+1] = temp;
            exch0 = 1;
         }
      }
      if (exch0 || !trips) {
#pragma omp  for  
         for (i = 1; i < N-1; i += 2) {
            if (A[i] > A[i+1]) {
               temp = A[i]; A[i] = A[i+1]; A[i+1] = temp;
               exch1 = 1;
            }
         }
      }
      } // end parallel
      trips = 1;
   }
}

void init_data()
{
   int i,j,t;
   for (i = 0; i < NN; ++i)
      A[i] = i;

   for (i = 0; i < NN; ++i) {
      j = rand() % NN;
      t = A[i]; A[i] = A[j]; A[j] = t;
   }
}

int main(int argc, char* argv[])
{   

   init_data();

   for (size_t i = 0; i < NN; ++i) 
      printf("%3d ",A[i]);
   printf("\n\n");

   OESort(A, NN);

   for (size_t j = 0; j < NN; ++j) 
      printf("%3d ",A[j]);
   printf("\n\n");
   
   return 0;
}
