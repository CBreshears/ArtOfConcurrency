#include "SortSelect.h"
//#include "tbb/blocked_range.h"
//#include "tbb/parallel_for.h"

class FindMedians {
	int *S;
	int *M;

public:
	FindMedians(int *_S, int *_Medians): S(_S), M(_Medians){}

	FindMedians(FindMedians& x, split): S(x.S), M(x.M) {}

	void operator()( const blocked_range<int>& r ) const {
		int i, j;
		for (j = r.begin(); j < r.end(); j++) {
			i = j * Q;
			M[j] = SortSelect5(&S[i], 3);  // find medians of subsequences
		}
	}
};
