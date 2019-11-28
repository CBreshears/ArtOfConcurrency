#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
using namespace tbb;

class PackingMove {
	const int *scanIdx;
	int *sPack;
	const int *S;

public:
	PackingMove(const int sIdx_[], int sPack_[], const int *S_) : 
		scanIdx(sIdx_), sPack(sPack_), S(S_) {}

	PackingMove(const int sIdx_[], int sPack_[], const int *S_, split) : 
		scanIdx(sIdx_), sPack(sPack_), S(S_) {}

	void operator()(const blocked_range<int>& r) const {
		for (int i = r.begin(); i < r.end(); i++) {
			if (scanIdx[i-1] != scanIdx[i])
				sPack[scanIdx[i]-1] = S[i];
		}
	}
};