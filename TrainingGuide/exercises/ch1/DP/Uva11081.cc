// Uva11081	Strings
// ³Â·æ
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXLEN = 64;
char A[MAXLEN], B[MAXLEN], C[MAXLEN];
int ALen, BLen, CLen, D[MAXLEN][MAXLEN][MAXLEN];

int dfs(int ia, int ib, int ic)
{
	int& ans = D[ia][ib][ic];
	if(ans >= 0) return ans;
	
	ans = 1;
	if(ic == 0) return ans;
	
	char c = C[CLen - ic];
	int subAns = 0, i;
	for(i = ALen - ia; i < ALen; i++)
		if(A[i] == c) subAns += dfs(ALen-i-1, ib, ic - 1);
	
	for(i = BLen - ib; i < BLen; i++)
		if(B[i] == c) subAns += dfs(ia, BLen-i-1, ic - 1);
	
	ans = (ans*subAns) % 10007;
	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);
	
	while(T--)
	{
		scanf("%s%s%s", A, B, C);
		ALen = strlen(A);
		BLen = strlen(B);
		CLen = strlen(C);
		memset(D, -1, sizeof(D));
		
		printf("%d\n", dfs(ALen, BLen, CLen));
	}
	return 0;
}

/* Ranking	Submission	Run Time	Language	Submission Date
   66	    8402998	    1.940	    C++	        2010-11-20 03:11:17 */