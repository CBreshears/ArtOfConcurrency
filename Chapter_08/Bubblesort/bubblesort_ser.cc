/**
 * @file bubblesort_ser.cc
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
 * @section DESCRIPTION Serial implementation of Bubblesort
 *                    
 * @section CITATION
 *          Example 8-1 from "The Art of Concurrency" (O'Reilly Media, 2009)
 **/
#include <process.h>
#include <stdio.h>

#define NN 100

int A[NN];

void BubbleSort(int *A, int N)
{
  int i, j;
  int temp;
  for (i = N-1; i > 0; i--) {
    for (j = 0; j < i; j++) {
      if (A[j] > A[j+1]) {
        temp = A[j]; A[j] = A[j+1]; A[j+1] = temp;
      }
    }
  }
}

void init_data()
{
	int i, x, y;
	for (i = 0; i < NN; i++)
		A[i] = i;
	for (i = 0; i < NN; i++) {
		x = rand() % NN;
		y = A[x]; A[x] = A[i]; A[i] = y;
	}
}

int main(int argc, char* argv[])
{	
	int i, j;

	init_data();

	for ( i = 0; i < NN; i++) printf("%3d ",A[i]);
	printf("\n\n");

 	BubbleSort(A,NN);

	for ( j = 0; j < NN; j++) printf("%3d ",A[j]);
	return 0;
}
