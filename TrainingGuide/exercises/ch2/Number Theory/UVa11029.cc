// UVa 11029 Leading and Trailing
// ³Â·æ
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int pow_mod(int base, int pow, int mod)
{
	if(pow == 0) return 1;
	
	long long result = pow_mod(base, pow / 2, mod);
	result *= result;
	
	if(pow % 2 == 1) result *= (base % mod);
	return (int)(result % mod);
}

double pow_lead(double base, int k)
{
	if(k == 0) return 1.0;
	
	double result = pow_lead(base, k/2);
	result *= result;
	
	if(k % 2 == 1) result *= base;
	
	while(result > 1000000000)
		result /= 1000000000;
	
	return result;
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t--)
	{
		int n, k, T;
		char buf[128];
		double L;
		scanf("%d%d", &n, &k);
		
		L = pow_lead((double)n, k);
		sprintf(buf, "%f", 1000 * L);
		// puts(buf);
		
		buf[3] = 0;
		
		T = pow_mod(n % 1000, k, 1000);
		printf("%s...%03d\n", buf, T);
	}
	return 0;
}

 
/* Ranking Submission Run Time Language Submission Date 
	142 	8455383 	0.012 	C++ 	2010-12-13 05:02:11  */
