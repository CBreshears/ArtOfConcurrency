// Serial version of Depth-first Search

#include <windows.h>
#include <stdio.h>
#include "TSStack.h"

#define V 10

int visited[V];
int adj[V][V];
int count = 0;

/*
void visit(int k)
{
	int i;
	
	 // Do something to VISIT node k

	visited[k] = ++count;
	for (i = 0; i < V; i++)
	{
		if (adj[k][i]) 
			if (!visited[i]) visit(i);
	}
}

void DFSearch()
{
	int k;

	for (k = 0; k < V; k++) visited[k] = 0;
	for (k = 0; k < V; k++) 
		if (!visited[k]) visit(k);
}

*/
void iDFSearch()
{
  int i, k;

 // for (k = 0; k < V; k++) visited[k] = 0;
  for (k = V-1; k >= 0; k--) {
    push(k);
  }
  while (stackSize() > 0) {
    pop((LPVOID *) &k);
    if (!visited[k]) {
      visited[k] = ++count;
      /*
        Do something to VISIT node k
      */
    
		for (i = V-1; i >= 0; i--)
		{
		 if (adj[k][i]) push(i);
		}
	}
  } // end while
}


void init_data()
{
	int i,j, k;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) 
			adj[i][j] = 0;
		visited[i] = 0;
	}
	for (k = 0; k < 5*V; k++){
		i = rand() % V;
		j = rand() % V;
		if (i != j) adj[i][j] = 1;
	}
}

int main(int argc, char* argv[])
{	
	init_data();
	initStack();
	for (int i=0; i<V; i++){
		printf("%3d: ",i);
		for (int j=0; j<V; j++)
			printf ("%d ",adj[i][j]);
		printf("\n");
	}

	//DFSearch();
	iDFSearch();

	for (int r = 0; r < V; r++) {

		printf("Node %3d visited %3d\n", r, visited[r] );

	}
	printf("\n\n");

	return 0;
}