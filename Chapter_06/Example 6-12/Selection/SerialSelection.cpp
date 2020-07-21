// Serial version of Selection algorithm

#include <windows.h>
#include <process.h>
#include <stdio.h>

#include "SortSelect.h"

#define N 29
#define Q 5     // Assumes fixed value of five; Modifiy 'Q' functions if value is other than five

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
			printf("SortLessThanQ Error: num not in [1..4]   num = %d\n",num);
			return -1;
	}
}

int SequentialSelect(int *S, int num, int k)
{
	if (num <= Q) return SortLessThanQ(S, num, k);

	int tNum = num/Q + 1;
	int *Medians = new int[tNum];
    int i = 0;
	for (int j = 0; j < num/Q; j++) {
		Medians[j] = SortSelect5(&S[i], 3);  // find medians of subsequences
		i += Q;
	}
	int lastNum = num - (Q * (num / Q));
	if (lastNum) {
		int lastQ = Q * (num / Q);
		Medians[tNum-1] = SortLessThanQ(&S[lastQ], lastNum, (lastNum+1)/2); 
	}
	else tNum--;

	int M = SequentialSelect(Medians, tNum, tNum/2);

	int leg[3] = {0,0,0};
	int *markS = new int[num];
	CountAndMark(S, markS, num, M, leg);

	if (leg[0] >= k) {
		int *sPack = new int[leg[0]];
		ArrayPack(S, sPack, leg[0], markS, 0);
		return SequentialSelect(sPack, leg[0], k);
	}
	else if ((leg[0] + leg[1]) >= k) return M;
	else {
		int *sPack = new int[leg[2]];
		ArrayPack(S, sPack, leg[2], markS, 2);
		return SequentialSelect(sPack, leg[2], k-(leg[0]+leg[1]));
	}
}

void init_data()
{
	int i;
	for (i = 0; i < N; i++){
		S[i] = rand() % N;
		//S[i] = i+1;
	}
}

int main(int argc, char* argv[])
{	

	init_data();

	for (int j = 0; j < N; j++){
		printf("%3d ",S[j]);
	}
	printf("\n\n");

	for (int r = 1; r <= N; r++) {

		int i = SequentialSelect(S, N, r);
		printf("r = %d i = %d\n", r, i);
	//	init_data();
	}
	for (int j = 0; j < N; j++){
		printf("%3d ",S[j]);
	}
	printf("\n\n");

	return 0;
}