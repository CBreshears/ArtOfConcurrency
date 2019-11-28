// Serial version of All-Pairs Shortest Path

#include <windows.h>
#include <float.h>
#include <stdio.h>


#define V 10

void Floyds(float **D)
{
  int i, j, k;

  for (k = 0; k < V; k++) {
	  for (i = 0; i < V; i++) {
		  for (j = 0; j < V; j++)
			  D[i][j] = min(D[i][j], D[i][k]+D[k][j]);
	  }
  }
}


void init_data(float **W, float **D)
{
	int i,j, k;
	for (i = 0; i < V; i++) {
		W[i] = new float[V];
		D[i] = new float[V];
		for (j = 0; j < V; j++) 
			D[i][j] = W[i][j] = FLT_MAX;
		D[i][i] = W[i][i] = 0.0;
	}
	for (k = 0; k < 5*V; k++){
		i = rand() % V;
		j = rand() % V;
		if (i != j) D[i][j] = W[i][j] = rand()%(V*V)/(float) V;
	}
}

int main(int argc, char* argv[])
{	
	float **W = new float*[V];
	float **D = new float*[V];

	init_data(W,D);

	for (int i=0; i<V; i++){

		for (int j=0; j<V; j++){
			if (W[i][j] == FLT_MAX) 
				printf("*** ");
			else printf ("%3.1f ",W[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	//DFSearch();
	Floyds(D);

	for (int i=0; i<V; i++){
		for (int j=0; j<V; j++){
			printf ("%3.1f ",D[i][j]);
		}
		printf("\n");
	}



	return 0;
}