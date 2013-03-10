// UVa 10616 Divisible Group Sums
// 陈锋
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 201, MAXQ = 10, MAXD = 20, MAXM = 11;

long long DP[MAXN][MAXM][MAXD];
int Num[MAXN];

long long dp(int n, int m, int r, const int& D)
{
	long long& ans = DP[n][m][r];
	if(ans != -1) return ans;
	
	ans = 0;
	if(m == 1)
	{
		for(int i = 0; i < n; i++)
			if(Num[i]%D == r) ans++;
	}
	else if(n == m)
	{
		int sum = 0;
		for(int i = 0; i < n; i++)
			sum += Num[i]%D;

		if(sum % D == r) ans++;
	}
	else if(n > m)
	{
		// 最后一个待选元素的所有可能
		for(int i = m - 1; i < n; i++)
			ans += dp(i, m - 1, (D + r - (Num[i])%D)%D, D);
	}
			
	#ifdef DEBUG
	printf("n = %d, m = %d, r = %d, ans = %d\n", n,m,r, ans);
	#endif
		
	return ans;
}

int main()
{
	int N, Q, D, M, set = 0, q;
	
	while(true)
	{
		scanf("%d%d", &N, &Q);
		if(N == 0 && Q == 0) break;
		
		for(int i = 0; i < N; i++)
			scanf("%d", &(Num[i]));
		
		printf("SET %d:\n", ++set);
		q = 0;
		while(q < Q)
		{
			memset(DP, -1, sizeof(DP));
			scanf("%d%d", &D, &M);
			#ifdef DEBUG
			printf("D = %d, M = %d\n", D, M);
			#endif
			
			printf("QUERY %d: %lld\n", ++q, dp(N, M, 0, D));
		}
	}

	return 0;
}