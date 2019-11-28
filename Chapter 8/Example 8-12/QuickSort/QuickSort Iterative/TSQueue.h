#include "quicksort.h"

typedef struct qNode *Qptr;

typedef struct qNode{
	qParams *Q;
	Qptr next;
} QNode;

extern void initQueue();
extern void enqueue(LPVOID);
extern int dequeue(LPVOID *);