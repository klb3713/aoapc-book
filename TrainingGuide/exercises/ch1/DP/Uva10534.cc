// Uva10534	Wavio Sequence
// 陈锋
#include <cstdio>
#include <algorithm>

using namespace std;

int readint()
{
	int num;
	scanf("%d", &num);
	return num;
}

const int MAXN = 10240;
int S[MAXN], LIS[MAXN], LDS[MAXN], BUF[MAXN];

int main()
{
	int N, i, k;
	while(scanf("%d", &N) == 1)
	{
		for(i = 0; i < N; i++)
			S[i] = readint();
		
		k = 0;
		BUF[k++] = S[0];
		for(i = 1; i < N; i++)
		{
			if(S[i] > BUF[k-1]) 
			{
				BUF[k++] = S[i];
				LIS[i] = k;
			}
			else 
			{
				int *lb = lower_bound(BUF, BUF + k, S[i]);
				*lb = S[i];
				LIS[i] = lb - BUF + 1;
			}
			#ifdef DEBUG
			printf("S[%d] = %d, LIS[%d] = %d \n", i, S[i], i, LIS[i]);
			#endif
		}
		
		k = 0;
		BUF[k++] = S[N-1];
		LDS[N-1] = k;
		for(i = N - 2; i >= 0; i--)
		{
			if(S[i] > BUF[k-1]) 
			{
				BUF[k++] = S[i];
				LDS[i] = k;
			}
			else 
			{
				int *lb = lower_bound(BUF, BUF + k, S[i]);
				*lb = S[i];
				LDS[i] = lb - BUF + 1;
			}
			#ifdef DEBUG
			printf("S[%d] = %d, LDS[%d] = %d \n", i, S[i], i, LDS[i]);
			#endif
		}
		
		int ans = 1;
		for(i = 0; i < N; i++)
			ans = max(ans, 2 * min(LIS[i], LDS[i]) - 1);
		printf("%d\n", ans);
	};
	return 0;
}

/* O(nlogn)的算法是从这里学的： http://blog.pfan.cn/rickone/13086.html
	Ranking	Submission	Run Time	Language	Submission Date
	34		8407566	 	0.100		C++			2010-11-21 23:42:45 */