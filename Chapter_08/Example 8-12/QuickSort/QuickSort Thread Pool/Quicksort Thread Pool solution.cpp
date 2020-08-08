// Quicksort Thread Pool solution.cpp : Threaded version of Quicksort algorithm using a fixed size thread pool, 
//                                      semaphores, events, and thread-safe queue data structure.  
//
#include <windows.h>
#include <process.h>
#include <stdio.h>
#include "TSQueue.h"

#define N 100
#define NUMTHREADS 2

DWORD WINAPI QuickSort(int, int);

int A[N];
long tCount = 0; 
HANDLE hSem;		// Semaphore to control access to remove index pairs from (non-empty) queue
HANDLE tSignal;		// Event to signal when sorting is completed (all elements have been a pivot)

int Partition (int p, int r)
{
	int x = A[p];
	int k = p;
	int l = r+1;
	int t;
	while (1)
	{
		do 
		  k++;
		while ((A[k] <= x) && (k < r));
		do 
		  l--;
		while (A[l] > x);

		while (k < l) {
			t = A[k];  A[k] = A[l];  A[l] = t;
			do k++; while (A[k] <= x);
			do l--; while (A[l] > x);
		}
		t = A[p];  A[p] = A[l];  A[l] = t;
		return l;
	}
}

unsigned __stdcall QuickSort(LPVOID pArg)
{
	int p;
	int r;
	int q;
	qParams *d=NULL, *d1, *d2;
	long t;

	printf("Thread started\n");

	while (1) {
		WaitForSingleObject(hSem, INFINITE);  // Semaphore count corresponds to number of items on queue
		dequeue((LPVOID *)&d);   //ignore return value from dequeue
		p = d->lo;
		r = d->hi;
		free(d);
		if (p < r) 
		{
			q = Partition(p, r);
			InterlockedIncrement(&tCount);
			d1 = (qParams *) malloc(sizeof(qParams));
			d1->lo = p;
			d1->hi = q-1;
			enqueue(d1);
			d2 = (qParams *) malloc(sizeof(qParams));
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
	for (i = 0; i < N; i++)
		A[i] = i;
	for (i = 0; i < N; i++) {
		j = rand() % N;
		t = A[i]; 
		A[i] = A[j];
		A[j] = t;
	}
}
int main(int argc, char* argv[])
{
	int q;
	int i;
	HANDLE hThreads[NUMTHREADS];
	qParams *e1, *e2;

	init_data();
	initQueue();
	tSignal = CreateEvent(NULL, TRUE, FALSE, NULL);

	for (i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\n\n");

	//Start threads in suspended mode until the initial partitioning is done
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

	for ( i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\nTCOUNT = %d\n", tCount);
	return 0;
}