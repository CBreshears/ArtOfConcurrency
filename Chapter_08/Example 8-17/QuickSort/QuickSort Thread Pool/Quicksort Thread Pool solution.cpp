// Quicksort Thread Pool solution.cpp : Threaded version of Quicksort algorithm using a fixed size thread pool, 
//                                      semaphores, events, and thread-safe queue data structure.  
//
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include "TSQueue.h"

#define NN 100
#define NUM_THREADS 2

//DWORD WINAPI QuickSort(int, int);

long tCount = 0; 
BOOL Done = FALSE;
HANDLE hSem;		// Semaphore to control access to remove index pairs from (non-empty) queue
HANDLE tSignal;		// Event to signal when sorting is completed (all elements have been a pivot)
int A[1000];

int Partition (int p, int r)
{	int x = A[p];
	int k = p;
	int l = r+1;
	int t;

	do k++; while ((A[k] <= x) && (k < r));
	do l--; while (A[l] > x);

	while (k < l) {
		t = A[k];  A[k] = A[l];  A[l] = t;
		do k++; while (A[k] <= x);
		do l--; while (A[l] > x);
	}
	t = A[p];  A[p] = A[l];  A[l] = t;
	return l;
}

unsigned __stdcall QuickSort(LPVOID pArg)
{
	int p, r, q;
	qSortIndex *d = NULL, *d1, *d2;
	int t = 0;
    int N = *((int *) pArg);

//	printf("Thread started\n");

	while (1) {
		WaitForSingleObject(hSem, INFINITE); 
		if (Done) break; //external signal to terminate threads 
		dequeue(&d);
		p = d->lo;
		r = d->hi;
		free(d);
		if (p < r) 
		{
			q = Partition(p, r);
			InterlockedIncrement(&tCount);
			d1 = new qSortIndex;
			d1->lo = p;
			d1->hi = q-1;
			enqueue(d1);
			d2 = new qSortIndex;;
			d2->lo = q+1;
			d2->hi = r;
			enqueue(d2);
			ReleaseSemaphore(hSem, 2, NULL);  // Two items added to queue; increment semaphore count by 2
		}
		else if (p == r) {
			t = InterlockedIncrement(&tCount);
			if (t == N) SetEvent(tSignal);   // Signal main thread that sorting is done
		}
	}
	return 0;
}

void init_data()
{
	int i,j,t;
	for (i = 0; i < NN; i++)
		A[i] = i;
	for (i = 0; i < NN; i++) {
		j = rand() % NN;
		t = A[i]; 
		A[i] = A[j];
		A[j] = t;
	}
}
int main(int argc, char* argv[])
{
  int i;
  HANDLE hThreads[NUM_THREADS];
  qSortIndex *e1;
  int NumToSort = NN;

  init_data();
  initQueue();
  tSignal = CreateEvent(NULL, TRUE, FALSE, NULL);

  for (i = 0; i < NN; i++) printf("%3d ",A[i]);
  printf("\n\n");

// Initialize semaphore with 1 item on the queue
  tCount = 0L;
  e1 = new qSortIndex;
  e1->lo = 0; e1->hi = NumToSort-1;
  enqueue(e1);

  hSem = CreateSemaphore(NULL, 1, NumToSort, NULL);

 //Start threads in suspended mode until the initial partitioning is done
  for (i = 0; i < NUM_THREADS; i++)
    hThreads[i] = (HANDLE) _beginthreadex(NULL, 0, QuickSort, &NumToSort, 0, NULL);
      
 
  WaitForSingleObject(tSignal, INFINITE); // Wait for signal

  Done = TRUE;
  ReleaseSemaphore(hSem, NUM_THREADS, NULL);
/*
for (i = 0; i < NUMTHREADS; i++)
		hThreads[i] = (HANDLE) _beginthreadex(NULL, 0, QuickSort, NULL, CREATE_SUSPENDED, NULL);

	q = Partition(0, N-1);
	InterlockedIncrement(&tCount);
	e1 = (qParams *) malloc(sizeof(qParams)); e1->lo = 0; e1->hi = q-1;
	enqueue((LPVOID)e1);
	e2 = (qParams *) malloc(sizeof(qParams)); e2->lo = q+1; e2->hi = N-1;
	enqueue((LPVOID)e2);
	hSem = CreateSemaphore(NULL, 2, N, NULL);	// Initialize semaphore with 2 items on the queue

	for (i = 0; i < NUMTHREADS; i++)
		ResumeThread(hThreads[i]);		// Resume execution of the sorting threads

	WaitForSingleObject(tSignal, INFINITE);  // Wait for signal from thread that sort is complete 
	for (i = 0; i < NUMTHREADS; i++)
		if (!TerminateThread(hThreads[i], i)) printf("Thread #%d failed to terminate\n",i);
*/

	for ( i = 0; i < NN; i++) printf("%3d ",A[i]);
	printf("\nTCOUNT = %d\n", tCount);
	return 0;
}