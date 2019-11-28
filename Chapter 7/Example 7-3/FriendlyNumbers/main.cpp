#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int u, int v)
{
if (v == 0) return u;
return gcd(v, u % v);
}
void FriendlyNumbers (int start, int end)
{
int last = end-start+1;
int *the_num = new int[last];
int *num = new int[last];
int *den = new int[last];
#pragma omp parallel
{ int i, j, factor, ii, sum, done, n;
// -- MAP --
#pragma omp for schedule (dynamic, 16)
for (i = start; i <= end; i++) {
ii = i - start;
sum = 1 + i;
the_num[ii] = i;
done = i;
factor = 2;
while (factor < done) {
if ((i % factor) == 0) {
sum += (factor + (i/factor));
if ((done = i/factor) == factor) sum -= factor;
}
factor++;
}
num[ii] = sum; den[ii] = i;
n = gcd(num[ii], den[ii]);
num[ii] /= n;
den[ii] /= n;
} // end for
// -- REDUCE --
#pragma omp for schedule (static, 8)
for (i = 0; i < last; i++) {
for (j = i+1; j< last; j++) {
if ((num[i] == num[j]) && (den[i] == den[j]))
printf ("%d and %d are FRIENDLY \n", the_num[i], the_num[j]);
}
}
} // end parallel region
}


int main(int argc, char **argv)
{
	unsigned int start = 1;
	unsigned int end = 2000;

    FriendlyNumbers(start, end);
}