// Bubblesrot.cpp : Threaded version of Bubblesort algorithm.  
//
#include <windows.h>
#include <process.h>
#include <stdio.h>

#define N 100
#define NUM_LOCKS 3
#define NUM_THREADS 2


int A[N];
CRITICAL_SECTION BLock[NUM_LOCKS];
BOOL Done = FALSE;
int iCounter = N-1;


unsigned __stdcall BubbleSort(LPVOID pArg)
{
	int i, j, k, releasePoint, temp, rpInc;
	BOOL exch;

	rpInc = N / NUM_LOCKS;
	rpInc++;

	while (!Done) {
		k = 0;
		exch = FALSE;
		EnterCriticalSection(&BLock[k]);
		  i = iCounter--;
		  releasePoint = rpInc;
//		  rpInc++;
		  if (i <= 0) {
			  Done = TRUE;
			  LeaveCriticalSection(&BLock[k]);
			  break;
		  }

		  for (j = 0; j < i; j++) {
			  if (A[j] > A[j+1]) {
				  temp = A[j]; A[j] = A[j+1]; A[j+1] = temp;
				  exch = TRUE;
			  }
			  if (j == releasePoint) {
				  LeaveCriticalSection(&BLock[k++]);
				  EnterCriticalSection(&BLock[k]);
				  releasePoint += rpInc;
			  }
		  }
		LeaveCriticalSection(&BLock[k]);
		if (!exch) Done = TRUE;
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
	int i, j;
	HANDLE hThread[NUM_THREADS];

	init_data();

	for ( i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\n\n");

	for ( j = 0; j < NUM_LOCKS; j++)
		InitializeCriticalSection(&BLock[j]);

//	BubbleSort(NULL);
	for ( i = 0; i < NUM_THREADS; i++)
		hThread[i] = (HANDLE) _beginthreadex(NULL, 0, BubbleSort, NULL, 0, NULL);

	WaitForMultipleObjects(NUM_THREADS, hThread, TRUE, INFINITE);

	for ( j = 0; j < N; j++) printf("%3d ",A[j]);
	return 0;
}
