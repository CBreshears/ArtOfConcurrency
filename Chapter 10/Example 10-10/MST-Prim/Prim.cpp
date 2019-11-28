// Serial version of Prim's MST algorithm

#include <windows.h>
#include <float.h>
#include <stdio.h>

#define V 20



void Prims(float **W, int **T, int N)
{
  int i, j, k;
  int *nearest = new int[N];
  float *mindist = new float[N];
  float min;

  for (i = 1; i < N; i++) {
	  nearest[i] = 0;
	  mindist[i] = W[i][0];
  }
  for (i = 0; i < N-1; i++) {
	  min = FLT_MAX;
	  for (j = 1; j < N; j++) {
		  if (0 <= mindist[j] && mindist[j] < min) {
			  min = mindist[j];
			  k = j;
		  }
	  }
	  T[i][0] = nearest[k];
	  T[i][1] = k;
	  mindist[k] = -1;
	  for (j = 1; j < N; j++) 
		  if (W[j][k] < mindist[j]) {
			  mindist[j] = W[j][k];
			  nearest[j] = k;
		  }
  } // for i
  return;
}


void init_data(float **W)
{
	int i,j, k;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			W[i][j] = FLT_MAX;
			W[j][i] = W[i][j];
		}
		W[i][i] = 0.0;
	}
	for (k = 0; k < 5*V; k++){
		i = rand() % V;
		j = rand() % V;
		if (i != j) {
			W[i][j] = (rand()%100) / 10.0; 
			W[j][i] = W[i][j];
		}
	}
}

int main(int argc, char* argv[])
{	
	float **W = new float*[V];
	int **MSTree = new int*[V];
	float val = 0.0;

	for (int i = 0; i < V; i++) {
		W[i] = new float[V];
		MSTree[i] = new int[2];
	}
	init_data(W);

	for (int i=0; i<V; i++){

		for (int j=0; j<V; j++){
			if (W[i][j] == FLT_MAX) 
				printf("*** ");
			else printf ("%3.1f ",W[i][j]);
		}
		printf("\n");
	}
	printf("\n\nEdges in MSTree:\n");
	//DFSearch();
	Prims(W, MSTree, V);

	for (int i=0; i<V-1; i++){
		int j = MSTree[i][0];
		int k = MSTree[i][1];
		val += W[j][k];
			printf ("(%d %d) ",j,k);
	}
		printf("\nVal = %5.3f\n", val);
	return 0;
}