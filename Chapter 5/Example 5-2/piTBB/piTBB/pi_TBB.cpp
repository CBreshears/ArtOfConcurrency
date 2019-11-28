#include <stdio.h>
#include <time.h>
//#include <cassert>


//#include <math.h>
//#include <cstdlib>
//#include <cctype>
#include "tbb/parallel_reduce.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/partitioner.h"

using namespace std;
using namespace tbb;

//#define Nthreads	2
//#define GrainSize      10000
long num_rects =  100000;


class MyPi {
	double *const my_rects;
public:
	double partialHeight;
	void operator()( const blocked_range<size_t>& r ) {
		double rectangleWidth = *my_rects;
		double x;
	    for (size_t i = r.begin(); i != r.end(); ++i)
		{
			x = (i + .5)*rectangleWidth;
			partialHeight += 4.0/(1.+ x*x);
		}
	}

	MyPi( MyPi& x, split ) : my_rects(x.my_rects), partialHeight(0) {}

	void join( const MyPi& y ) {partialHeight += y.partialHeight;}

	MyPi(double *const width) : my_rects(width), partialHeight(0) {}

};



int main(int argc, char* argv[])
{
	double area;
	double width = 1./(double)num_rects;
	MyPi my_block((double *const)&width);
    task_scheduler_init init;

	parallel_reduce(blocked_range<size_t>(0,num_rects), my_block, auto_partitioner());
	area = my_block.partialHeight*width;

	printf("The value of PI is %15.12f\n",area);

	return 0;
}