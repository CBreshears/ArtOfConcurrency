#include "tbb/parallel_scan.h"
#include "tbb/blocked_range.h"
using namespace tbb;

class PackingScan {
	int sum;
	int* const y;
	const int* const x;
	const int symbol;

public:
	PackingScan(int y_[], const int x_[], const int sym_) : 
	            sum(0), x(x_), y(y_), symbol(sym_) {}

	template<typename Tag>
	void operator()(const blocked_range<int> &r, Tag) {
		int temp = sum;
		for (int i = r.begin(); i < r.end(); ++i) {
			if (x[i] == symbol) temp++;
			if(Tag::is_final_scan())
				y[i] = temp;
		}
		sum = temp;
	}

	PackingScan(PackingScan& b, split) : 
	            sum(0), x(b.x), y(b.y), symbol(b.symbol) {}
	void reverse_join(PackingScan& a) {sum = a.sum + sum;}
	void assign(PackingScan& b) {sum = b.sum;}
};
