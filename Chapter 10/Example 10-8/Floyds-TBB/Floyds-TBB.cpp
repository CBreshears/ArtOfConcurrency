// Parallel version of All-Pairs Shortest Path (Floyd's Algorithm)

#include <windows.h>
#include <float.h>
#include <stdio.h>
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range2d.h"
#include "tbb/partitioner.h"

using namespace tbb;

#define V 10
#define rGrainSize 2
#define cGrainSize 2

class tryK {
	const int k;
	float **D;

public:
	tryK (const int k_, float **D_) : k(k_), D(D_) {}

	tryK (const int k_, float **D_,  split) : k(k_), D(D_) {}

	void operator() ( const blocked_range2d<int,int>& r ) const {
		for (int i = r.rows().begin(); i < r.rows().end(); i++) {
		  for (int j = r.cols().begin(); j < r.cols().end(); j++)
			  D[i][j] = min(D[i][j], D[i][k]+D[k][j]);
	    }
	}
};

void cFloyds(float **D)
{
  int k;
  for (k = 0; k < V; k++) 
	  parallel_for(blocked_range2d<int, int> (0, V, rGrainSize, 0, V, cGrainSize), tryK(k, D));
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
{	task_scheduler_init init;

	float **W = new float*[V];
	float **D = new float*[V];

	init_data(W,D);


	for (int i=0; i<V; i++){

		for (int j=0; j<V; j++){
			if (W[i][j] == FLT_MAX) 
				printf("*** ");
			else printf ("%3.1f ",W[i][j]);
			D[i][j] = W[i][j];
		}
		printf("\n");
	}
	printf("\n\n");
	//DFSearch();
	cFloyds(D);

	for (int i=0; i<V; i++){
		for (int j=0; j<V; j++){
			printf ("%3.1f ",D[i][j]);
		}
		printf("\n");
	}



	return 0;
}