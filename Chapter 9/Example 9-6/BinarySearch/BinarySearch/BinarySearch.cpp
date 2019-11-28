// Serial version of Linear Search

#include <windows.h>
#include <stdio.h>

#define N 20

int S[N];

void BinarySearch (int *A, int lo, int hi, int key, int *position)
{
	int mid;
	*position = -1;  // assume not found

	while (lo <= hi) {
		mid = (lo + hi) / 2;
		if (A[mid] > key)
			hi = mid - 1;
		else if (A[mid] < key)
			lo = mid + 1;
		else {
			*position = mid; // found
			break; 
		}
	}
}

void init_data()
{
	int i;
	for (i = 0; i < N; i++){
		//S[i] = rand() % N;
		S[i] = i*2;
	}
}

int main(int argc, char* argv[])
{	
	int pos;

	init_data();

	for (int j = 0; j < N; j++){
		printf("%3d ",S[j]);
	}
	printf("\n\n");

	for (int r = 1; r <= N; r++) {

		BinarySearch(S, 0, N-1, r, &pos);
		if (pos != -1) printf("key = %d found at index %d\n", r, pos );
		else printf("key = %d NOT found.\n",r);
	//	init_data();
	}
	printf("\n\n");

	return 0;
}