// UVa 11444 Sum
// ³Â·æ
#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 100001, MOD = 1000000009, MAXK = 21;
typedef long long Int64;
Int64 S[MAXN][MAXK], C[MAXK];
int n, q, Seq[MAXN]; //--C(k,0), C(k,1), C(k,2)... C(k, k);

//ÁîS(n, k) = ¡Æseq[i]*ik, i = 1 to n

Int64 pow_mod(int i, int k)
{
	if(k == 0) return 1;
	i = (i % MOD + MOD) % MOD;

	Int64 result = pow_mod(i, k/2);
	result *= result;
	result %= MOD;
	
	if(k % 2 == 1) result *= i;
	result %= MOD;

	return (int)result;
}

void fill_S(int n)
{
	memset(S, 0, sizeof(S));
	for(int k = 0; k < MAXK; k++)
		for(int i = 1; i <= n; i++)
		{
			S[i][k] = S[i-1][k] + (Seq[i-1] * pow_mod(i, k)) % MOD;
			S[i][k] %= MOD;
		}
}

void fill_C(int k)
{
	C[0] = 1;
	for(int i = 1; i <= k; i++)
		C[i] = C[i-1] * (k-i+1) / i;

	for(int i = 0; i <= k; i++)
		C[i] %= MOD;
}


//ÔòF(k,a,b) = C(k,0) * (S(b, k) - S(a-1, k)) + C(k,1) * (1-a)(S(b,k-1) - S(a-1, k-1))
//	+ ... + C(k,x) * (1-a)^x * (S(b, k-1) - S(a-1, k-1))
int F(int k, int a, int b)
{
	Int64 result = 0;
	for(int i = 0; i <= k; i++)
	{
		Int64 temp = C[i] * pow_mod(1-a, i) % MOD * (S[b][k-i] - S[a-1][k-i]);
		temp = (temp%MOD + MOD) % MOD;
		result = (result + temp) % MOD;
	}

	return (int)(result);
}

int main()
{
	int T;
	scanf("%d", &T);
	
	while(T--)
	{
		scanf("%d", &n);
		for(int i = 0; i < n; i++)
			scanf("%d", &Seq[i]);
		fill_S(n);
		
		scanf("%d", &q);
		for(int i = 0; i < q; i++)
		{
			int k,a,b;
			scanf("%d%d%d", &k, &a, &b);
			fill_C(k);
			printf("%d\n", F(k,a,b));
		}
	}
	return 0;
}
//Ranking	Submission	Run Time	Language	Submission Date
//65		8478569		2.808		C++		2010-12-25 15:05:24
