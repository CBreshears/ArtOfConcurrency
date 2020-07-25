/**
 * @file CountAndMark.h
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
 * @section DESCRIPTION LEG and CountMark classes for parallel selection 
 *          using TBB; LEG holds the number of elements that are less than,
 *          equal to, and greater than the median value; CountAndMark finds 
 *          the number of elements within the three partitions and determine
 *          the partition of each element (via TBB parallel_reduce)
 *
 * @section CITATION
 *          Example 6-14 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/

class LEG {

public:
   int less;
   int equal;
   int greater;

   LEG(): less(0), equal(0), greater(0) {}
};

class CountAndMark {
   int *S;
   int *Marks;
   int median;

public:
   LEG leg;

   CountAndMark(int *_S, int *_Marks, int _median):
      S(_S), Marks(_Marks), median(_median) {}

   CountAndMark(CountAndMark& x, split):
      S(x.S), Marks(x.Marks), median(x.median) {}

   void operator()(const blocked_range<size_t>& r) {

      for (size_t i = r.begin(); i != r.end(); ++i) {
         if (S[i] < median) {Marks[i] = 0; leg.less++;}
         else if (S[i] == median) {Marks[i] = 1; leg.equal++;}
         else {Marks[i] = 2; leg.greater++;}
      }
   }
   void join (const CountAndMark& y) {
      leg.less += y.leg.less;
      leg.equal += y.leg.equal;
      leg.greater += y.leg.greater;
   }
};
