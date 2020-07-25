/**
 * @file map_reduce_omp.cc
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
 * @section DESCRIPTION (Serial and) OpenMP implementation of computing friendly
 *                      number pairs within given range using MapReduce 
 *                 
 * @section CITATION
 *          Example 7-3 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int u, int v)
{
   if (v == 0) return u;
   return gcd(v, u % v);
}

void FriendlyNumbers (int start, int end)
{
   int last = end-start+1;
   int *the_num = new int[last];
   int *num = new int[last];
   int *den = new int[last];

#pragma omp parallel
{  
   int i, j, factor, ii, sum, done, n;

// -- MAP --
   #pragma omp for schedule (dynamic, 16)
   for (i = start; i <= end; ++i) {
      ii = i - start;
      sum = 1 + i;
      the_num[ii] = i;
      done = i;
      factor = 2;
   
      while (factor < done) {
         if ((i % factor) == 0) {
            sum += (factor + (i/factor));
            if ((done = i/factor) == factor) sum -= factor;
         }
         factor++;
      }
   
      num[ii] = sum; den[ii] = i;
      n = gcd(num[ii], den[ii]);
      num[ii] /= n;
      den[ii] /= n;
   } // end for

// -- REDUCE --
   #pragma omp for schedule (static, 8)
   for (i = 0; i < last; ++i) {
      for (j = i+1; j< last; ++j) {
         if ((num[i] == num[j]) && (den[i] == den[j]))
            printf ("%d and %d are FRIENDLY \n", the_num[i], the_num[j]);
      }
   }
} // end parallel region
 
} // end FriendlyNumbers 

int main(int argc, char **argv)
{
   unsigned int start = 1;
   unsigned int end = 2000;

   FriendlyNumbers(start, end);
}
