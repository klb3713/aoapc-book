// UVa10990 Another New Function
// ³Â·æ
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int MAXM = 2000001;
int PHI[MAXM], DPHI[MAXM], SUMDPHI[MAXM];

void GeneratePhi()
{
	fill_n(PHI, MAXM, 0);
	PHI[1] = 1;
	for(int i = 2; i < MAXM; i++)
	{
		if(!PHI[i])
		{
			for(int j = i; j < MAXM; j += i)
			{
				if(!PHI[j]) PHI[j] = j;
				PHI[j] = PHI[j] / i * (i - 1);
			}
		}
	}
}

int main()
{
	GeneratePhi();
	
	DPHI[1] = 0;
	SUMDPHI[1] = DPHI[1];
	for(int i = 2; i < MAXM; i++)
	{
		DPHI[i] = 1 + DPHI[PHI[i]];
		SUMDPHI[i] = DPHI[i] + SUMDPHI[i-1];
	}
	
	int N, m, n;
	scanf("%d", &N);
		
	while(N--)
	{
		scanf("%d%d", &m, &n);
		int result = SUMDPHI[n] - SUMDPHI[m-1];
		
		printf("%d\n", result);
	}
	
	return 0;
}

/* Ranking Submission Run Time Language Submission Date 
	21 		8465284 	0.220 	C++ 	2010-12-18 03:19:19 
 */