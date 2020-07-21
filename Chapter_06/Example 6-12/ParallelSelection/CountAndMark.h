//#include "tbb/parallel_reduce.h"
//#include "tbb/blocked_range.h"

class LEG {

public:
	int less;
	int equal;
	int greater;

	LEG(): less(0), equal(0), greater(0) {}
};

class CountAndMark {
	int *S;
	int *Marks;
	int median;

public:
	LEG leg;

	CountAndMark(int *_S, int *_Marks, int _median):
		S(_S), Marks(_Marks), median(_median) {}

	CountAndMark(CountAndMark& x, split):
		S(x.S), Marks(x.Marks), median(x.median) {}

	void operator()(const blocked_range<size_t>& r) {

		for (size_t i = r.begin(); i != r.end(); ++i) {
			if (S[i] < median) {Marks[i] = 0; leg.less++;}
			else if (S[i] == median) {Marks[i] = 1; leg.equal++;}
			else {Marks[i] = 2; leg.greater++;}
		}
	}
	void join (const CountAndMark& y) {
		leg.less += y.leg.less;
		leg.equal += y.leg.equal;
		leg.greater += y.leg.greater;
	}
};
