// Parallel version of Prim's MST algorithm using OpenMP and Intel TBB

#include <windows.h>
#include <float.h>
#include <stdio.h>
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"


using namespace tbb;
#define V 20

class NearestNeighbor {
	const float *const NNDist;
public:
	float minDistVal;
	int minDistIndex;

	void operator()( const blocked_range<int>& r ) {
//		const float *a = NNDist;
		for( int j = r.begin(); j != r.end(); ++i ) {
			if (0 <= NNDist[j] && NNDist[j] < minDistVal) {
				minDistVal = NNDist[j];
				minDistIndex = j;
			}
		}
	}

	NearestNeighbor( const float *nnd ) :
		NNDist(nnd), minDistVal(FLT_MAX), minDistIndex(-1) {}

	NearestNeighbor( NearestNeighbor& x, split ) :
		NNDist(x.NNDist), minDistVal(FLT_MAX), minDistIndex(-1) {}

	void join( const NearestNeighbor& y ) {
		if (y.minDistVal < x.minDistVal) {
			minDistVal = y.minDistVal;
			minDistIndex = y.minDistIndex;
		}
	}
};

int NodeNearestToTree( float *a, int n ) 
{
	NearestNeighbor Node(a);
	parallel_reduce(blocked_range<int>(0,n), Node, auto_partitioner());
	return Node.minDistIndex;
}

void cPrims(float **W, int **T, int N)
{
  int i, j, k;
  int *nearNode = new int[N];
  float *minDist = new float[N];
  float min;

  for (i = 1; i < N; i++) {
	  nearNode[i] = 0;
	  minDist[i] = W[i][0];
  }
  for (i = 0; i < N-1; i++) {

	  k = NodeNearestToTree(minDist, N);
	  
	  T[i][0] = nearNode[k];
	  T[i][1] = k;
	  minDist[k] = -1;
	  
#pragma omp parallel for shared(k)
	  for (j = 1; j < N; j++) 
		  if (W[j][k] < minDist[j]) {
			  minDist[j] = W[j][k];
			  nearNode[j] = k;
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
	task_scheduler_init init;

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
	cPrims(W, MSTree, V);

	for (int i=0; i<V-1; i++){
		int j = MSTree[i][0];
		int k = MSTree[i][1];
		val += W[j][k];
			printf ("(%d %d) ",j,k);
	}
		printf("\nVal = %5.3f\n", val);
	return 0;
}