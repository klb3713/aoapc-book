// UVa 10325 The Lottery
// ³Â·æ
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long int64;
const int MAXM = 15, MAXSET = 1<<15;
int N, M, num[MAXM];
int64 LCM[MAXSET];

int64 gcd(int64 a, int64 b)
{
	return b == 0 ? a : gcd(b, a%b);
}

int64 lcm(int64 a, int64 b)
{
	int64 l = a / gcd(a, b) * b;
	return l;
}

int64 lcm(int s)
{
	int64& ans = LCM[s];
	if(ans) return ans;
	
	for(int i = 0; i < M; i++)
		if(s & (1<<i))
			return ans = lcm(lcm(s & (~(1<<i))), (long long)num[i]);
	
	return ans = 1;
}

int bitcnt(int s)
{
	int k = 0;
	for(; s != 0; s >>= 1) if(s&1) k++;
	return k;
}

int main()
{
	while(scanf("%d%d", &N, &M) == 2)
	{
		for(int i = 0; i < M; i++)
			scanf("%d", &(num[i]));
		
		fill_n(LCM, MAXSET, 0);
		LCM[0] = 1;
		
		int64 n = N, l;
		for(int i = 1; i < (1<<M); i++)
		{
			l = lcm(i);
			
			int cnt = bitcnt(i);
			
			l = N / l;
			if(cnt%2 == 1) l = -l;
			// printf("lcmset(%x) = %lld\n", i, l);
			n += l;
		}
		printf("%d\n", (int)n);
	}
	
	return 0;
}
 
/* Ranking Submission Run Time Language Submission Date 
	51 		8455613 	0.044 	C++ 	2010-12-13 08:54:16  */
