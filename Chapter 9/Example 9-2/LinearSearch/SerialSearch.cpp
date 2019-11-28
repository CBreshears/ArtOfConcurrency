// Serial version of Linear Search

#include <windows.h>
#include <stdio.h>
#include <omp.h>

#define NN 20

int S[NN];

void LinearSearch (int *A, int N, int key, int *position)
{
	int i;
	*position = -1;  // assume not found

#pragma omp parallel for
	for (i = 0; i < N; i++) {
		if (A[i] == key) {
			*position = i;
			break;
		}
	}
}

void init_data()
{
	int i,j,t;
	for (i = 0; i < NN; i++)
		S[i] = i;
	for (i = 0; i < NN; i++) {
		j = rand() % NN;
		t = S[i]; 
		S[i] = S[j];
		S[j] = t;
	}
}

int main(int argc, char* argv[])
{	
	int pos;

	init_data();

	for (int j = 0; j < NN; j++){
		printf("%3d ",S[j]);
	}
	printf("\n\n");

	for (int r = 1; r <= NN; r++) {

		LinearSearch(S, NN, r, &pos);
		if (pos != -1) printf("key = %d found at index %d\n", r, pos );
		else printf("key = %d NOT found.\n",r);
	//	init_data();
	}
	printf("\n\n");

	return 0;
}