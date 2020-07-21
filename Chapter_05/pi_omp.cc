/**
 * @file pi_omp.cc
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
 * @section DESCRIPTION Serial and OpenMP implementation of numerical 
 *                      integration code 
 * @section CITATION
 *          Example 5-1 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/

#include <stdio.h>
#include <omp.h>

long long num_rects = 10000000;


int main(int argc, char* argv[])
{
   double mid, height, width, sum=0.0;
   long long i;
   double area;
   width = 1. / (double)num_rects;

#pragma omp parallel for private(mid, height) reduction(+:sum)
   for (i = 0; i < num_rects; ++i) {
      mid = (i + .5) * width;
      height = 4.0 / (1. + mid * mid);
      sum += height;
   }
   area = width * sum;

   printf("The value of PI is %15.12f\n",area);
   return 0;
}