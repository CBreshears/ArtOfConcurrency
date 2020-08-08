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

void enqueue(LPVOID d)
{
	QNode *t = (QNode *) malloc(sizeof(QNode));
	t->Q = (qParams *)d;
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