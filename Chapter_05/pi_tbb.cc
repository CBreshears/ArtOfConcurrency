/**
 * @file pi_tbb.cc
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
 * @section DESCRIPTION Threading Building Blocks implementation of numerical 
 *                      integration code 
 * @section CITATION
 *          Example 5-2 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/

#include <stdio.h>
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"
#include "tbb/partitioner.h"

using namespace std;
using namespace tbb;

long num_rects =  100000;

class MyPi {
   double *const my_rects;

public:
   double partialHeight;

   void operator()( const blocked_range<size_t>& r ) {
      double rectangleWidth = *my_rects;
      double x;
      for (size_t i = r.begin(); i != r.end(); ++i) {
         x = (i + .5)*rectangleWidth;
         partialHeight += 4.0/(1.+ x*x);
      }
   }

   MyPi( MyPi& x, split ) : my_rects(x.my_rects), partialHeight(0) {}
   
   void join( const MyPi& y ) {partialHeight += y.partialHeight;}

   MyPi(double *const width) : my_rects(width), partialHeight(0) {}

};

int main(int argc, char* argv[])
{
   double area;
   double width = 1./(double)num_rects;
   MyPi my_block((double *const)&width);

   parallel_reduce(blocked_range<size_t>(0,num_rects), my_block, auto_partitioner());
   area = my_block.partialHeight*width;

   printf("The value of PI is %15.12f\n",area);

   return 0;
}
