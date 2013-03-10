// UVa11317 GCD+LCM
// ³Â·æ
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;
const int MAXN = 1000001;

int phi[MAXN];
double LG[MAXN], C[MAXN], LL[MAXN], SL[MAXN];

void GeneratePhi()
{
	fill_n(phi, MAXN, 0);
	phi[1] = 1;
	for(int i = 2; i < MAXN; i++)
	{
		if(!phi[i])
		{
			for(int j = i; j < MAXN; j += i)
			{
				if(!phi[j]) phi[j] = j;
				phi[j] = phi[j] / i * (i - 1);
			}
		}
	}
}

//Cn=lg(¡Ç(gcd(i, n))), i = 1 ~ n-1 
//= lg( ¡Æs^(phi(n/s)) ), s|n
//= ¡Æs*lg(phi(n/s))
void GenerateCn()
{
	fill_n(LG, MAXN, 0.0);
	for(int i = 1; i <= MAXN / 2; i++)
	{
		if(i > 1 && C[i] == 0.0)
			C[i] = log10((double)(i - 1));

		for(int j = i + i; j < MAXN; j += i)
			C[j] += ((double)i) * log10((double)phi[j/i]);
	}
}

// G[N]
void GenerateLG()
{
	fill_n(LG, MAXN, 0.0);
	for(int i = 1; i < MAXN; i++)
	{
		LG[i] = C[i] + LG[i-1];
	}
}

// ¡Ælg(i), i = 1 ~ N
void GenerateSL()
{
	SL[1] = 0.0;
	for(int i = 2; i < MAXN; i++)
	{
		SL[i] = log10((double)i) + SL[i-1];
	}
}

int main()
{
	GeneratePhi();
	GenerateCn();
	GenerateLG();
	GenerateSL();

	int N;
	while(true)
	{
		scanf("%d", &N);
		if(N == 0) break;

		long long lcm = (long long)ceil(((N-1)*SL[N] - LG[N]) / 100);
		printf("%lld %lld\n",(long long)ceil(LG[N]/100), lcm);
	}

	return 0;
}