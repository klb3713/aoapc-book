// UVA 10710 Chinese Shuffle
// ³Â·æ
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
typedef long long Int64;

Int64 pow2mod(int power, int mod)
{
	if(power == 0) return 1;
	Int64 result = pow2mod(power / 2, mod);
	result = (result * result) % mod;
	if(power%2 == 1) result = (result * 2) % mod;

	return result;
}

int main()
{
	int n;
	while(true)
	{
		scanf("%d", &n);
		if(n == -1) break;

		int mod = n%2 ? n : n - 1;
		bool isJimmy = pow2mod(n - 1, mod) == 1;
		printf("%d is %sa Jimmy-number\n", n, isJimmy ? "" : "not ");
	}

	return 0;
}
//Ranking	Submission	Run Time	Language	Submission Date
//29		8488995		0.016		C++			2011-01-01 04:46:45