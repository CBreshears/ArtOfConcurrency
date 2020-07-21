// Parallel version of Prefix Sum algorithm

#include <windows.h>
#include <process.h>
#include <stdio.h>

#define NUM_THREADS 4
#define N 100

//int A[16] ={3,5,2,5,7,9,-4,6,7,-3,1,7,6,8,-1,2};
int A[N];
int inTotals[NUM_THREADS], outTotals[NUM_THREADS];
HANDLE doneStep1[NUM_THREADS];
HANDLE doneStep2;

unsigned __stdcall prefixSum(LPVOID pArg)
{
	int myid = *((int *) pArg);
	int start, end, i;
	int lPrefixTotal;

	free(pArg);
    start = (N / NUM_THREADS) * myid;
	end = (N / NUM_THREADS) * (myid + 1);
	if (myid == (NUM_THREADS-1)) end = N;

	// Step 1
	for (i = start+1; i < end; i++) 
		A[i] = A[i-1] + A[i];
    inTotals[myid] = A[end-1];

	SetEvent(doneStep1[myid]); //signal completion of Step 1

	WaitForSingleObject(doneStep2, INFINITE); // wait for completion of Step 2

	// Step 3
	lPrefixTotal = outTotals[myid];   
	printf("id: %d  lPT = %d\n",myid, lPrefixTotal);
	for (i = start; i < end; i++) 
		A[i] = lPrefixTotal + A[i];

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
	HANDLE tH[NUM_THREADS];

	init_data();

	for (i = 0; i < NUM_THREADS; i++) 
		doneStep1[i] = CreateEvent(NULL, TRUE, FALSE, NULL); // manual reset event initially unsignaled
	doneStep2 = CreateEvent(NULL, TRUE, FALSE, NULL); // manual reset event initially unsignaled

	for ( i = 0; i < N; i++) printf("%3d ",A[i]);
	printf("\n\n");

	for (i = 0; i < NUM_THREADS; i++) {
		int *tnum = new int;
		*tnum = i;
        tH[i] = (HANDLE) _beginthreadex(NULL, 0, prefixSum, (LPVOID) tnum, 0, NULL);
	}

	WaitForMultipleObjects(NUM_THREADS, doneStep1, TRUE, INFINITE); // wait for Step 1 completion

//	for ( j = 0; j < NUM_THREADS; j++) printf("%3d ",inTotals[j]);
//	printf("\n");

	// Step 2
	outTotals[0] = 0;
	for (j = 1; j < NUM_THREADS; j++) {
		outTotals[j] = outTotals[j-1] + inTotals[j-1];
	}


//    for ( j = 0; j < NUM_THREADS; j++) printf("%3d ",outTotals[j]);
//	printf("\n");

	SetEvent(doneStep2);  //signal completion of Step 2

	WaitForMultipleObjects(NUM_THREADS, tH, TRUE, INFINITE); // wait for completion of Step 3

	for ( j = 0; j < N; j++) printf("%3d ",A[j]);
	printf("\n");
	return 0;
}