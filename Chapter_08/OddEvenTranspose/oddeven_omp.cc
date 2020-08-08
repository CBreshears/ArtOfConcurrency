/**
 * @file oddeven_omp.cc
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
 * @section DESCRIPTION Serial and OpenMP implementation of Odd-Even 
 *                      Transposition sort
 * @section CITATION
 *          Example 8-3 and 8-4 from "The Art of Concurrency" 
 *                                   (O'Reilly Media, 2009)
 **/
#include <stdlib.h>
#include <stdio.h>

#define N 100

int A[N];

void OESort(int NN, int *A)
{
   int exch = 1, start = 0, i;
   int temp;

   while (exch || start) {
      exch = 0;
#pragma omp parallel for private(temp) 
      for (i = start; i < NN-1; i+=2) {
         if (A[i] > A[i+1]) {
            temp = A[i]; A[i] = A[i+1]; A[i+1] = temp;
            exch = 1;
         }
      }
      if (start == 0) start = 1;
      else start = 0;
   }
}

void init_data()
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

   init_data();

   for ( i = 0; i < N; i++) printf("%3d ",A[i]);
   printf("\n\n");

   OESort(N,A);

   for ( j = 0; j < N; j++) printf("%3d ",A[j]);
   printf("\n\n");
   
   return 0;
}
