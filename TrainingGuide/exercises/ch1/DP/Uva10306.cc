// Uva10306	e-Coins
// ³Â·æ
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

int readint()
{
	int num;
	scanf("%d", &num);
	return num;
}

const int MAXM = 40, MAXS = 301;
int m, S, Coins[MAXM][2], DP[MAXS][MAXS], VIS[MAXS][MAXS];

int dp(int x, int y)
{
	int& minAns = DP[x][y];
	if(VIS[x][y]) return minAns;
	VIS[x][y] = 1;
	
	if(x == 0 && y == 0) return minAns = 0;
	minAns = INT_MAX;
	
	for(int i = 0; i < m; i++)
		if(x >= Coins[i][0] && y >= Coins[i][1])
		{
			int ans = dp(x-Coins[i][0], y-Coins[i][1]);
			if(ans != INT_MAX)
				minAns = min(minAns, 1 + ans);
		}

	return minAns;
}

int main()
{
	int n = readint(), i, j;
	while(n--)
	{
		m = readint();
		S = readint();
		
		for(i = 0; i < m; i++)
		{
			Coins[i][0] = readint();
			Coins[i][1] = readint();
		}
		memset(VIS, 0, sizeof(VIS));
		
		int minAns = INT_MAX;
		for(i = 0; i < MAXS; i++)
			for(j = i; j < MAXS; j++)
				if(j*j + i*i == S*S)
				{
					minAns = min(dp(i, j), minAns);
					minAns = min(dp(j, i), minAns);
				}
		
		if(minAns == INT_MAX) puts("not possible");
		else printf("%d\n", minAns);
	}
	
	return 0;
}


/* Ranking	Submission	Run Time	Language	Submission Date
	99		8404192		0.024		C++			2010-11-20 14:51:46 */