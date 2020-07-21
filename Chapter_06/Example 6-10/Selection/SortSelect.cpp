#define swap(A,B) {int t; t = A; A = B; B = t;}

int SortSelect2 (int S[], int k)
{
	if (S[0] > S[1]) swap(S[0], S[1]);
	if (k == 1) return S[0];
	else return S[1];
}

int SortSelect3 (int S[], int k)
{
	if (S[0] > S[1]) swap(S[0], S[1]);
	if (S[1] > S[2]) swap(S[1], S[2]);	
	if (S[0] > S[1]) swap(S[0], S[1]);
	return S[k-1];
}

int SortSelect4 (int S[], int k)
{
	if (S[0] > S[1]) swap(S[0], S[1]);
	if (S[1] > S[2]) swap(S[1], S[2]);	
	if (S[0] > S[1]) swap(S[0], S[1]);
	if (S[2] > S[3]) swap(S[2], S[3]);
	if (S[1] > S[2]) swap(S[1], S[2]);	
	if (S[0] > S[1]) swap(S[0], S[1]);
    return S[k-1];
}

int SortSelect5 (int S[], int k)
{
	if (S[0] > S[1]) swap(S[0], S[1]);
	if (S[1] > S[2]) swap(S[1], S[2]);	
	if (S[0] > S[1]) swap(S[0], S[1]);
	if (S[2] > S[3]) swap(S[2], S[3]);
	if (S[1] > S[2]) swap(S[1], S[2]);	
	if (S[0] > S[1]) swap(S[0], S[1]);
	if (S[3] > S[4]) swap(S[3], S[4]);
	if (S[2] > S[3]) swap(S[2], S[3]);
	if (S[1] > S[2]) swap(S[1], S[2]);	
	if (S[0] > S[1]) swap(S[0], S[1]);

    return S[k-1];
}

void CountAndMark(int S[], int Marks[], int num, int median, int leg[3])
{
	for (int i = 0; i < num; i++) {
		if (S[i] == median) {Marks[i] = 1; leg[1]++;}
		else if (S[i] < median) {Marks[i] = 0; leg[0]++;}
		else {Marks[i] = 2; leg[2]++;}
	}
}
/*
void ArrayPack(int S[], int sPack[], int num, int Marks[], int scanSym)
{
	int i, j=0;
	i = 0;
	do {
		if (Marks[i] == scanSym) sPack[j++] = S[i];
		i++;
	} while (j < num);

}
*/
void ArrayPack(int S[], int sPack[], int num, int Marks[], int scanSym)
{
	int i, j=0;
	for (int i = 0; i < num; i++)
		if (Marks[i] == scanSym) sPack[j++] = S[i];
}
