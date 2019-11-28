#include <windows.h>
#include <stdio.h>
#include "TSStack.h"

CRITICAL_SECTION sCS;

SNode *top;
int sCount;

void initStack()
{
	InitializeCriticalSection(&sCS);
	top = NULL;
    sCount = 0;
}

void push(int d)
{
//	printf("push %d\n",d);
	SNode *t = (SNode *) malloc(sizeof(SNode));
	t->node = d;
	EnterCriticalSection(&sCS);
	   t->next = top;
	   top = t;
	   sCount++;
    LeaveCriticalSection(&sCS);
}

int pop(LPVOID *d)
{
	SNode *ptr;
	if (top){
		EnterCriticalSection(&sCS);
		   ptr = top;
		   top = top->next;
		LeaveCriticalSection(&sCS);
//		printf("pop %d\n",ptr->node);
   		*d = (LPVOID)ptr->node;
		free(ptr);
		sCount--;
		return 0;
	}
	else {
		return 1;
	}
}

int stackSize()
{
	return sCount;
}