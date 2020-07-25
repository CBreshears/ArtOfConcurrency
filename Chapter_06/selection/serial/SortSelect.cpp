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
 *          CountAndMark() counts the number of elements in array S[] that
 *          are less than, equal to, or greater than median;
 *          ArrayPack() moves the appropriate elements based on Marks[]
 *
 * @section CITATION
 *          Example 6-11 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/

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

void CountAndMark(int S[], int Marks[], int num, int median, int leg[3])
{
   for (int i = 0; i < num; i++) {
      if (S[i] == median) {Marks[i] = 1; leg[1]++;}
      else if (S[i] < median) {Marks[i] = 0; leg[0]++;}
      else {Marks[i] = 2; leg[2]++;}
   }
}

void ArrayPack(int S[], int sPack[], int num, int Marks[], int scanSym)
{
   int i, j=0;
   i = 0;
   do {
      if (Marks[i] == scanSym) sPack[j++] = S[i];
      i++;
   } while (j < num);
}
