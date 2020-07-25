/**
 * @file SortSelect.cpp
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
 * @section DESCRIPTION Collection of O(1) routines to sort fixed number
 *          of integers and return chosen (k-th) element of sorted order;
 *          ArrayPack() moves the appropriate elements based on Marks[]
 *
 * @section CITATION
 *          Used in code from Example 6-12 from "The Art of Concurrency" 
 *                                              (O'Reilly Media, 2009)
 **/

#include "PackingScan.h"
#include "PackingMove.h"
#include "tbb/partitioner.h"

#include <stdio.h>

#define swap(A,B) {int t; t = A; A = B; B = t;}

int SortSelect2 (int S[], int k)
{
   if (S[0] > S[1]) swap(S[0], S[1]);
   if (k == 1) return S[0];
   else return S[1];
}

int SortSelect3 (int S[], int k)
{
   if (S[0] > S[1]) swap(S[0], S[1]);
   if (S[1] > S[2]) swap(S[1], S[2]);   
   if (S[0] > S[1]) swap(S[0], S[1]);
   return S[k-1];
}

int SortSelect4 (int S[], int k)
{
   if (S[0] > S[1]) swap(S[0], S[1]);
   if (S[1] > S[2]) swap(S[1], S[2]);   
   if (S[0] > S[1]) swap(S[0], S[1]);
   if (S[2] > S[3]) swap(S[2], S[3]);
   if (S[1] > S[2]) swap(S[1], S[2]);   
   if (S[0] > S[1]) swap(S[0], S[1]);
   return S[k-1];
}

int SortSelect5 (int S[], int k)
{
   if (S[0] > S[1]) swap(S[0], S[1]);
   if (S[1] > S[2]) swap(S[1], S[2]);   
   if (S[0] > S[1]) swap(S[0], S[1]);
   if (S[2] > S[3]) swap(S[2], S[3]);
   if (S[1] > S[2]) swap(S[1], S[2]);   
   if (S[0] > S[1]) swap(S[0], S[1]);
   if (S[3] > S[4]) swap(S[3], S[4]);
   if (S[2] > S[3]) swap(S[2], S[3]);
   if (S[1] > S[2]) swap(S[1], S[2]);   
   if (S[0] > S[1]) swap(S[0], S[1]);

   return S[k-1];
}

void ArrayPack(int S[], int sPack[], int num, int Marks[], int scanSym)
{
   int *scanIdx = new int[num];
   PackingScan body(scanIdx, Marks, scanSym);

   parallel_scan(blocked_range<int>(0,num), body);//, auto_partitioner());

   if (scanIdx[0]) sPack[0] = S[0];  // move if first element is marked
   parallel_for(blocked_range<int>(1,num), PackingMove(scanIdx,sPack,S)); 
             //, auto_partitioner());
}

