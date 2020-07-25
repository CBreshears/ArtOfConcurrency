/**
 * @file PackingScan.h
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
 * @section DESCRIPTION PackingScan class for parallel selection using TBB;
 *          sets up the TBB class requirements to compute prefix scan on 
 *          the Marks array
 *
 * @section CITATION
 *          Example 6-16 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/

#include "tbb/parallel_scan.h"
#include "tbb/blocked_range.h"
using namespace tbb;

class PackingScan {
   int sum;
   int* const y;
   const int* const x;
   const int symbol;

public:
   PackingScan(int y_[], const int x_[], const int sym_) : 
               sum(0), x(x_), y(y_), symbol(sym_) {}

   template<typename Tag>
   void operator()(const blocked_range<int> &r, Tag) {
      int temp = sum;
      for (int i = r.begin(); i < r.end(); ++i) {
         if (x[i] == symbol) temp++;
         if(Tag::is_final_scan())
            y[i] = temp;
      }
      sum = temp;
   }

   PackingScan(PackingScan& b, split) : 
               sum(0), x(b.x), y(b.y), symbol(b.symbol) {}
   void reverse_join(PackingScan& a) {sum = a.sum + sum;}
   void assign(PackingScan& b) {sum = b.sum;}
};
