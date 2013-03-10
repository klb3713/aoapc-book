// UVa11181 Probability Given
// ³Â·æ
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;
const int MAXN = 20;

struct SetProb
{
	int s; // subset
	double P;
};

int bitcnt(int s)
{
	int cnt = 0;
	while(s)
	{
		if(s&1) cnt++;
		s >>= 1;
	}
	return cnt;
}

int main()
{
	vector<SetProb> setprobs;
	int N, r, Case = 1;
	double P[MAXN];

	while(true)
	{
		scanf("%d%d", &N, &r);
		if(N == 0 && r == 0) break;
		for(int i = 0; i < N; i++)
			scanf("%lf", &(P[i]));

		setprobs.clear();

		// P(i) = (¡ÆP(s) ,i is in s)/¡ÆP(s)
		double sumS = 0.0; // 
		SetProb prob;
		for(int s = 0; s < (1 << N); s++)
		{
			if(bitcnt(s) == r)
			{
				prob.s = s;
				prob.P = 1;
				for(int i = 0; i < N; i++)
				{
					if(prob.s & (1<<i)) prob.P *= P[i];
					else prob.P *= 1 - P[i];
				}
				setprobs.push_back(prob);
				sumS += prob.P;
			}
		}

		printf("Case %d:\n", Case++);
		for(int i = 0; i < N; i++)
		{
			double sum = 0.0;
			for(vector<SetProb>::iterator iter = setprobs.begin(); iter != setprobs.end(); iter++)
			{
				if(iter->s & (1<<i))
					sum += iter->P;
			}
			printf("%6f\n", sum / sumS);
		}
	}
	return 0;
}
//Ranking	Submission	Run Time	Language	Submission Date
//107		8475937		0.248		C++		2010-12-24 02:13:34
