// UVa 11287 - Pseudoprime Numbers
// ³Â·æ
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

int pow_mod(int a, int pow, int mod)
{
	if(pow == 0) return 1;
	
	long long result = pow_mod(a, pow / 2, mod);
	result *= result;
	result %= mod;
	
	if(pow %2 == 1) result *= a;
	
	return (int)(result % mod);
}

const int MAXP = 1000000000, MAX_PRIME = 31624;
bool IsPrime[MAX_PRIME];
vector<int> primes;

bool isprime(int num)
{
	if(num < MAX_PRIME)
		return IsPrime[num];
	
	for(vector<int>::iterator iter = primes.begin(); iter != primes.end(); iter++)
		if(num % *iter == 0) return false;
	
	return true;
}

int main()
{
	int p, a;
	
	fill_n(IsPrime, MAX_PRIME, true);
	IsPrime[2] = true;
	primes.reserve(MAX_PRIME);
	for(int i = 2; i < MAX_PRIME; i++)
	{
		if(IsPrime[i])
		{
			primes.push_back(i);
			for(int j = i*i; j < MAX_PRIME; j += i)
				IsPrime[j] = false;
		}
	}
	
	while(true)
	{
		scanf("%d%d", &p, &a);
		if(p == 0 && a == 0) break;
		
		bool result = !isprime(p);
		if(result)
			result = (pow_mod(a, p, p) == a);
		
		puts(result ? "yes" : "no");
	}
	
	return 0;
}

/* Ranking Submission Run Time Language Submission Date 
	194 	8454296 	0.012 	C++ 	2010-12-12 13:23:38  */

