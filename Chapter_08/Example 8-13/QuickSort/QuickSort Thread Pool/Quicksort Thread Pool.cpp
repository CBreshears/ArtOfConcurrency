// Quicksort Thread Pool.cpp : Threaded version of Quicksort algorithm using a fixed size thread pool and thread-safe 
//                             queue data structure.  There are two related problems with the code as is.
//
//    Problems: 1) Can't use return code from dequeue to determine if there are more things that
//                 might be added to the queue.  Threads could empty the queue of empty partitions
//                 while others are partitioning data; this would terminate the former too early.
//                 Some mechanism is needed to determine if there is anything on the queue (not part
//                 of the queue library) and pause threads if queue is empty, but may have items added.
//
//              2) How does the main thread know when all the sorting is done?  Can threads detect when 
//                 the sorting process is completed (as opposed to just having an empty queue the is waiting
//                 for a partitioning thread to enqueue a pair of index pairs) and terminate?  If the main
//                 thread were notified when the sorting was completed, it could call TerminateThread(HANDLE, DWORD)
//                 on each of the spawned threads before the process ended.  However, the main thread must 
//                 be assured that all work was done before starting to terminate threads.

//
#include <windows.h>
#include <stdio.h>
#include "TSQueue.h"

#define N 100
#define NUMTHREADS 2

int A[N];
long tCount = 0; // each element to be sorted will eventually be the pivot or single element in partition; 
                 //                   thus, will finish with value of N

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

DWORD WINAPI QuickSort(LPVOID pArg)
{
	int p;
	int r;
	int q;
	qParams *d=NULL, *d1, *d2;
	long t;

	printf("Thread started\n");

	while (1) {
		if (dequeue((LPVOID *)&d)) break;   // DANGEROUS TEST FOR MULTIPLE THREADS!!!  
											// Might terminate threads prematurely
		p = d->lo;
		r = d->hi;
		free(d);
		if (p < r)  // if there is one or more things to sort...
		{
			q = Partition(p, r);
			t = InterlockedIncrement(&tCount);

// encapsulate the indices for the lower portion of the partition and enqueue
			d1 = (qParams *) malloc(sizeof(qParams));
			d1->lo = p;
			d1->hi = q-1;
			enqueue(d1);

// encapsulate the indices for the upper portion of the partition and enqueue
			d2 = (qParams *) malloc(sizeof(qParams));
			d2->lo = q+1;
			d2->hi = r;
			enqueue(d2);
		}
		else if (p == r)  //... else count the single element partition
			t = InterlockedIncrement(&tCount);
	}
	return 0;
}

void init_data()
{
	int i;
	for (i = 0; i < N; i++)
		A[i] = rand() % N;
}

int main(int argc, char* argv[])
{
	int q;
	int i;
	HANDLE hThreads[NUMTHREADS];
	qParams *e1, *e2;

	init_data();
	initQueue();

	for (i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\n\n");

	//Start threads in suspended mode until the initial partitioning is done
	for (i = 0; i < NUMTHREADS; i++)
		hThreads[i] = CreateThread(NULL, 0, QuickSort, NULL, CREATE_SUSPENDED, NULL);

	q = Partition(0, N-1);
	InterlockedIncrement(&tCount);
	e1 = (qParams *) malloc(sizeof(qParams)); e1->lo = 0; e1->hi = q-1;
	enqueue((LPVOID)e1);
	e2 = (qParams *) malloc(sizeof(qParams)); e2->lo = q+1; e2->hi = N-1;
	enqueue((LPVOID)e2);

	// Start the sorting threads
	for (i = 0; i < NUMTHREADS; i++)
		ResumeThread(hThreads[i]);

	WaitForMultipleObjects(NUMTHREADS, hThreads, TRUE, INFINITE);  // wait for threads to terminate???
	                                                               // But, threads are in a potentially infinite loop
	                                                               // Is there some other way to signal sorting is done?

	for ( i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\nTCOUNT = %d\n", tCount);
	return 0;
}