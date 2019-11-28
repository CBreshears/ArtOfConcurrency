#include <windows.h>
#include "TSQueue.h"

CRITICAL_SECTION cs;

QNode *top, *end;

void initQueue()
{
	InitializeCriticalSection(&cs);
	top = NULL;
	end = NULL;
}

void enqueue(LPVOID e)
//
// enqueue is thread-safe since only one thread at a time may create and add a new node to the queue list
//
{
	QNode *t = (QNode *) malloc(sizeof(QNode));
	t->Q = (qParams *)e;
	t->next = NULL;
	EnterCriticalSection(&cs);
	   if (top != NULL) {
		   end->next = t;
		   end = t;
	   }
	   else {
		   top = t;
		   end = t;
	   }
    LeaveCriticalSection(&cs);
}

int dequeue(LPVOID *d)
//
// dequeue is thread-safe since only one thread at a time may remove a node from the queue list
// if no node is currently on the list (queue is empty), dequeue returns 1
//
{
	QNode *ptr;
	if (top){
		EnterCriticalSection(&cs);
		   ptr = top;
		   top = top->next;
		LeaveCriticalSection(&cs);
   		*d = (LPVOID)ptr->Q;
		free(ptr);
		return 0;
	}
	else {
		return 1;
	}
}