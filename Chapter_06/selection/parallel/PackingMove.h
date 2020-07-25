/**
 * @file PackingMove.h
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
 * @section DESCRIPTION PackingMove class for parallel selection using TBB;
 *          class declarations to pack the data items concurrently from the
 *          selected partition
 *
 * @section CITATION
 *          Example 6-17 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/

#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
using namespace tbb;

class PackingMove {
   const int *scanIdx;
   int *sPack;
   const int *S;

public:
   PackingMove(const int sIdx_[], int sPack_[], const int *S_) : 
      scanIdx(sIdx_), sPack(sPack_), S(S_) {}

   PackingMove(const int sIdx_[], int sPack_[], const int *S_, split) : 
      scanIdx(sIdx_), sPack(sPack_), S(S_) {}

   void operator()(const blocked_range<int>& r) const {
      for (int i = r.begin(); i < r.end(); ++i) {
         if (scanIdx[i-1] != scanIdx[i])
            sPack[scanIdx[i]-1] = S[i];
      }
   }
};
