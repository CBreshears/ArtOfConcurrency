// Concurrent version of Binary Search

#include <windows.h>
#include <stdio.h>


#define N 1900


void BinarySearch (int *A, int lo, int hi, int key, int NumInt, int *position)
{
	float offset, base;
	int *mid = new int[NumInt+1];
	char *locate = new char[NumInt+2];
	int i;

	locate[0] = 'R'; locate[NumInt+1] = 'L';
	while (lo <= hi && *position == -1) {
		int lmid;
		base = (float)(hi - lo + 1)/(NumInt+1);
		mid[0] = lo - 1;
		for (i = 1; i <= NumInt; i++) {
			offset = base*(i) + (i - 1);
			lmid = mid[i] = lo + (int)offset;
			if (lmid <= hi) {
				if (A[lmid] > key)
					locate[i] = 'L';
				else if (A[lmid] < key)
					locate[i] = 'R';
				else {
					locate[i] = 'E';
					*position = lmid; // found
				}
			}
			else {
				mid[i] = hi + 1;
				locate[i] = 'L';
			}
		}
		for (i = 1; i <= NumInt; i++) {
			if (locate[i] != locate[i-1]) {
				lo = mid[i-1] + 1;
				hi = mid[i] - 1;
			}
		}
		if (locate[NumInt] != locate[NumInt+1]) lo = mid[NumInt] +1;
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
		BinarySearch(S, 0, N-1, r, intervals, &pos);
		if (pos != -1) printf("key = %d found at index %d\n", r, pos );
		else printf("key = %d NOT found.\n",r);
	//	init_data();
	}
	printf("\n\n");

	return 0;
}