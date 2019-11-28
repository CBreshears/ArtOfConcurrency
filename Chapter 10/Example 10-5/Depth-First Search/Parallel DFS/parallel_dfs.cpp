// Concurrent version of Depth-first Search

#include <windows.h>
#include <process.h>
#include <stdio.h>
#include "TSStack.h"

#define V 5000
#define NUM_THREADS 4

long visited[V];
long order[V];
int adj[V][V];
long gCount = 0;

HANDLE hSem;		// Semaphore to control access to remove index pairs from (non-empty) queue
HANDLE tSignal;		// Event to signal when sorting is completed (all elements have been a pivot)



unsigned __stdcall  pDFSearch(void *pArg)
{
	int k, i, iWillVisit=0;

	while(1) {/*
		if (gCount == V) {
	//		printf("DONE\n");
			SetEvent(tSignal);
			break;
		}
		*/
		WaitForSingleObject(hSem, INFINITE);  // Semaphore count corresponds to number of items on stack
		if (gCount == V) break;
		pop((LPVOID *) &k); //ignore return value from pop
		if (!InterlockedCompareExchange(&visited[k], 1L, 0L)) {
			iWillVisit = 1;
			order[k] = InterlockedIncrement(&gCount);
		}
		if (iWillVisit) {
           /*
            Do something to VISIT node k
           */
			for (i = V-1; i >= 0; i--)
			{	long semCount=0;
				if (adj[k][i]) { 
					push(i);
					semCount++;
				}
				if (semCount) ReleaseSemaphore(hSem, semCount, NULL);
			}
			iWillVisit = 0;
			if (gCount == V) SetEvent(tSignal);
		}
	}
	return 0;
}

void init_data()
{
	int i,j, k;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) 
			adj[i][j] = 0;
		visited[i] = 0;
	}
	for (k = 0; k < 5*V; k++){
		i = rand() % V;
		j = rand() % V;
		if (i != j) adj[i][j] = 1;
	}
}


int main(int argc, char* argv[])
{

	int i;
	HANDLE hThreads[NUM_THREADS];

	init_data();
	initStack();
	tSignal = CreateEvent(NULL, TRUE, FALSE, NULL);

	for (i = V-1; i >= 0; i--) push(i);  // load up initial stack to cover connected components
	hSem = CreateSemaphore(NULL, V, V*V, NULL);	// Initialize semaphore with V items on the stack

	//Start threads in suspended mode until the initial partitioning is done
	for (i = 0; i < NUM_THREADS; i++)
		hThreads[i] = (HANDLE) _beginthreadex(NULL, 0, pDFSearch, NULL, 0, NULL);

	WaitForSingleObject(tSignal, INFINITE);  // Wait for signal from thread that sort is complete 
	printf("SIGNAL DONE\n");
	ReleaseSemaphore(hSem, NUM_THREADS, NULL);

	//for (i = 0; i < NUM_THREADS; i++)
	//	if (!TerminateThread(hThreads[i], i)) printf("Thread #%d failed to terminate\n",i);

		for (int r = 0; r < V; r++) {

		printf("Node %3d visited %3d\n", r, order[r] );

	}
	printf("\n\n");

	return 0;
}