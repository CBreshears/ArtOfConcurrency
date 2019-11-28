// Concurrent version of Linear Search

#include <windows.h>
#include <process.h>
#include <stdio.h>


#define N 19
#define NUM_THREADS 4

typedef struct {
	int *A;
	int num;
	int key;
	int tid;
} sParam;

BOOL done = FALSE;  // Initialize to not found

void LinearPSearch (int *A, int s, int e, int key, DWORD *position)
{
	int i; 

	for (i = s; i < e; i++) {
		if (done) return;
		if (A[i] == key) {
			*position = i;
			printf("Found it i = %d\n", i);
			done = TRUE;
			break;
		}
	}
	return;
}

unsigned __stdcall pSearch (LPVOID pArg) // Helper function
{
	sParam *inArg = (sParam *)pArg;
	int *A   = inArg->A;
	int num  = inArg->num;
	int key  = inArg->key;
	int tid  = inArg->tid;

	int start, end;
	DWORD pos = -1;

	start = (N/NUM_THREADS) * tid;
	end = (N/NUM_THREADS) * (tid+1);
	if (tid+1 == NUM_THREADS) end = N;

	LinearPSearch(A, start, end, key, &pos);
	free(pArg);
	ExitThread(pos);
}

void init_data(int *S)
{
	int i;
	for (i = 0; i < N; i++){
		S[i] = rand() % N;
		//S[i] = i+1;
	}
}

int main(int argc, char* argv[])
{	
	int S[N], i;
	int *position = new int;  
    int sKey = 34;
	HANDLE tH[NUM_THREADS];

	init_data(S);
	S[18] = 34;

	for (int j = 0; j < N; j++){
		printf("%3d ",S[j]);
	}
	printf("\n\n");

	for (i = 0; i < NUM_THREADS; i++) {
		sParam *pArg = new sParam;
		pArg->A = S;
		pArg->num = N;
		pArg->key = sKey;
		pArg->tid = i;
        tH[i] = (HANDLE) _beginthreadex(NULL, 0, pSearch, (LPVOID) pArg, 0, NULL);
	}

	WaitForMultipleObjects(NUM_THREADS, tH, TRUE, INFINITE);

	for (i = 0; i < NUM_THREADS; i++) {
		GetExitCodeThread(tH[i], (LPDWORD) position);
		if (*position != -1) {
			printf("key = %d found at index %d\n", sKey, *position ); 
			break;
		}
	}

	if (*position == -1) printf("key = %d NOT found.\n",sKey);

	printf("\n\n");

	return 0;
}