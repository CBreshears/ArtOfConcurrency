/**
 * @file shellsort_hpar_ser.cc
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
 * @section DESCRIPTION Modified serial implementation of Shellsort that will
 *                      sort an h-partition all at once
 *                   
 * @section CITATION
 *          Example 8-10 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/
#include <stdlib.h>
#include <stdio.h>

#define N 100

int A[N];

void InsertionSort(int P, int *A)
{
   size_t j;
   int v;

   for (size_t i = 1; i < P; ++i) {
      v = A[i]; 
      j = i;
      while (A[j-1] > v) {
         A[j] = A[j-1]; j--;
         if (j <= 0) break;
      }
      A[j] = v;
   }
}

void Shellsort2(int *A, size_t P)
{
   size_t i, j, k, h;
   int  v;

   h = 1; while (h < P) h = 3*h + 1;
   h /= 3;
   while (h != 1) {
      for (k = 0; k < h; ++k) {
         for (i = k+h; i < P; i+=h)  {
            v = A[i]; j = i;
            while (j >= h && A[j-h] > v) {
               A[j] = A[j-h]; 
               j -= h;
            }
            A[j] = v;
         } // for i
      }  // for k
      h /= 3;
   }
   InsertionSort(P,A);  // clean up
}


void init_data()
{
   int i, x, y, t;

   for (i = 0; i < N; ++i)
      A[i] = i;

   for (i = 0; i < N; ++i){
      x = rand() % N;
      t = A[x]; A[x] = A[i]; A[i] = t;
   }

}

int main(int argc, char* argv[])
{	
   size_t i, j;

   init_data();

   for ( i = 0; i < N; ++i) printf("%3d ",A[i]);
   printf("\n\n");
   
   Shellsort2(A, N);
   
   for ( j = 0; j < N; ++j) printf("%3d ",A[j]);
   printf("\n\n");

   return 0;
}
