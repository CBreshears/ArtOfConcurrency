// Parallel version of Selection algorithm

#include <windows.h>
#include <stdio.h>
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_reduce.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"
#include "tbb/parallel_scan.h"

using namespace tbb;

#include "SortSelect.h"
#include "CountAndMark.h"
#include "FindMedians.h"
#include "PackingScan.h"

#define N 29
//#define Q 5     // Assumes fixed value of five; Modifiy 'Q' functions if value is other than five

//int S[16] ={15,11,7,3,16,12,8,4,13,9,5,1,14,10,6,2};
//int S[16] ={3,5,2,5,7,9,-4,6,7,-3,1,7,6,8,-1,2};
int S[N];

int SortLessThanQ(int S[], int num, int k)
{
	switch (num)
	{
		case 1: 
			return S[0];
			break;
		case 2: 
			return SortSelect2(S, k);
			break;
		case 3: 
			return SortSelect3(S, k);
			break;
		case 4: 
			return SortSelect4(S, k);
			break;
		case 5: 
			return SortSelect5(S, k);
			break;
		default: 
			printf("SortLessThanQ Error: num not in [1..5]   num = %d\n",num);
			return -1;
	}
}

int ParallelSelect(int *S, int num, int k)
{
//	printf("SS num = %d\n", num);
	if (num <= Q) return SortLessThanQ(S, num, k);

	int cNum = num/Q + 1;
	int *Medians = new int[cNum];

	parallel_for(blocked_range<int>(0, num/Q, 5), FindMedians(S, Medians));

	int lastNum = num - (Q * (num / Q));
	if (lastNum) {
		int lastQ = Q * (num / Q);
		Medians[cNum-1] = SortLessThanQ(&S[lastQ], lastNum, (lastNum+1)/2); 
	}
	else cNum--;

	int M = ParallelSelect(Medians, cNum, (cNum+1)/2);

	int *markS = new int[num];
	CountAndMark camBody(S, markS, M);
	parallel_reduce(blocked_range<size_t>(0,num,5), camBody);

	int numLessEqual = camBody.leg.less + camBody.leg.equal;
	if (camBody.leg.less >= k) {
		int *sPack = new int[camBody.leg.less];
		ArrayPack(S, sPack, num, markS, 0);
		return ParallelSelect(sPack, camBody.leg.less, k);

	}
	else if ((numLessEqual) >= k) return M;
	else {
		int *sPack = new int[camBody.leg.greater];
		ArrayPack(S, sPack, num, markS, 2);
		return ParallelSelect(sPack, camBody.leg.greater, k-(numLessEqual));
	}
}

void init_data()
{
	int i, x, y;
	for (i = 0; i < N; i++){
		//S[i] = rand() % N;
		S[i] = i+1;
	}
	for (i = 0; i < N; i++){
		x = rand() % N;
		y = S[x]; S[x] = S[i]; S[i] = y;
	}
}

int main(int argc, char* argv[])
{	
	task_scheduler_init init;
	init_data();

	for (int j = 0; j < N; j++){
		printf("%3d ",S[j]);
	}
	printf("\n\n");

	for (int r = 1; r <= N; r++) {
//for (int r = 11; r == 11; r++) {
		int i = ParallelSelect(S, N, r);
		printf("r = %d i = %d\n", r, i);
	//	init_data();
	}
	for (int j = 0; j < N; j++){
		printf("%3d ",S[j]);
	}
	printf("\n\n");

	return 0;
}