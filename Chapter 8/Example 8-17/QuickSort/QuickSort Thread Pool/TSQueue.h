#include "quicksort.h"

typedef struct qNode *Qptr;

typedef struct qNode{
	qSortIndex *Q;
	Qptr next;
} QNode;

extern void initQueue();
extern BOOL notEmpty();
extern void enqueue(LPVOID);
extern int dequeue(LPVOID *);