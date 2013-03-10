// UVa10759 - Dice Throwing
// ³Â·æ
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long Int64;
const int MAXN = 25, MAXX = 150;
Int64 DP[MAXN][MAXX];

Int64 gcd(Int64 a, Int64 b)
{
	return b == 0 ? a : 
		gcd(b, a%b);
}

Int64 dp(int n, int x)
{
	Int64& ans = DP[n][x];
	if(ans != -1) return ans;
	ans = 0;

	if(x < n) return ans;

	if(n == 1) return ans = (x >= 1 && x <= 6) ? 1 : 0;

	for(int i = 1; i <= 6; i++)
	{
		if(x >= i) ans += dp(n-1, x-i);
	}

	return ans;
}

int main()
{
	memset(DP, -1, sizeof(DP));
	while(true)
	{
		int n,x;
		Int64 s, ans, g;
		scanf("%d%d", &n, &x);
		if(n == 0 && x == 0) break;

		s = 1;
		for(int i = 0; i < n; i++)
			s *= 6;
		ans = 0;
		for(int i = x; i <= 6*n; i++)
			ans += dp(n, i);

		if(ans == 0) 
			puts("0");
		else if(ans == s)
			puts("1");
		else
		{
			g = gcd(ans, s);
			ans /= g;
			s /= g;
			printf("%lld/%lld\n", ans, s);
		}
	}
	return 0;
}
//Ranking	Submission	Run Time	Language	Submission Date
//	238		8475993		0.012		C++		2010-12-24 02:55:55