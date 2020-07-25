/**
 * @file FindMedians.h
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
 * @section DESCRIPTION FindMedians class for parallel selection using TBB;
 *          methods for TBB to divid up the tasks and assign them to threads 
 *          through the parallel_for algorithm
 *
 * @section CITATION
 *          Example 6-13 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/

#include "SortSelect.h"

class FindMedians {
   int *S;
   int *M;

public:
   FindMedians(int *_S, int *_Medians): S(_S), M(_Medians){}

   FindMedians(FindMedians& x, split): S(x.S), M(x.M) {}

   void operator()( const blocked_range<int>& r ) const {
      int i, j;
      for (j = r.begin(); j < r.end(); ++j) {
         i = j * Q;
         M[j] = SortSelect5(&S[i], 3);  // find medians of subsequences
      }
   }
};
