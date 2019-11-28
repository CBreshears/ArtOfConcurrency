// Concurrent version of Binary Search

#include <windows.h>
#include <stdio.h>


#define N 1900


void NarySearch (int *A, int lo, int hi, int key, int Ntrvl, int *pos)
{
	float offset, step;
	int *mid = new int[Ntrvl+1];
	char *locate = new char[Ntrvl+2];
	int i;

	locate[0] = 'R'; locate[Ntrvl+1] = 'L';
	while (lo <= hi && *pos == -1) {
		int lmid;
		step = (float)(hi - lo + 1)/(Ntrvl+1);
		mid[0] = lo - 1;
		for (i = 1; i <= Ntrvl; i++) {
			offset = step*(i) + (i - 1);
			lmid = mid[i] = lo + (int)step;
			if (lmid <= hi) {
				if (A[lmid] > key)
					locate[i] = 'L';
				else if (A[lmid] < key)
					locate[i] = 'R';
				else {
					locate[i] = 'E';
					*pos = lmid; } // found
			}
			else {
				mid[i] = hi + 1;
				locate[i] = 'L';
			}
		}
		for (i = 1; i <= Ntrvl; i++) {
			if (locate[i] != locate[i-1]) {
				lo = mid[i-1] + 1;
				hi = mid[i] - 1;
			}
		}
		if (locate[Ntrvl] != locate[Ntrvl+1]) lo = mid[Ntrvl] +1;
	}
}

void init_data(int *S)
{
	int i;
	for (i = 0; i < N; i++){
		//S[i] = rand() % N;
		S[i] = i;
	}
}

int main(int argc, char* argv[])
{	
	int pos = -1;
	int S[N];
	int intervals = 4;

	init_data(S);

	for (int j = 0; j < N; j++){
		printf("%3d ",S[j]);
	}
	printf("\n\n");

	for (int r = 1; r <= N; r++) {
		pos = -1;
	//	int r = 127;
		NarySearch(S, 0, N-1, r, intervals, &pos);
		if (pos != -1) printf("key = %d found at index %d\n", r, pos );
		else printf("key = %d NOT found.\n",r);
	//	init_data();
	}
	printf("\n\n");

	return 0;
}