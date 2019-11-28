typedef struct sNode *Sptr;

typedef struct sNode{
	int node;
	Sptr next;
} SNode;

extern void initStack();
extern void push(int);
extern int pop(LPVOID *);
extern int stackSize();