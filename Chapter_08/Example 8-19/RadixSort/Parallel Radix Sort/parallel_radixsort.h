typedef struct {
	int *A;        // pointer to array to be sorted
	int num;       // number of items in A to be sorted
	int tid;       // thread id number
	int keylength; // number of bits in the key
} tParams;
