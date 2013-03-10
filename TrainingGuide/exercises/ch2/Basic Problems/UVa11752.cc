// UVa 11752 The Super Powers
// ³Â·æ
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

typedef unsigned long long LONGTYPE;
vector< LONGTYPE > results;
const int MAXEXP = 64;
bool isprime[MAXEXP];

LONGTYPE power(int i, int e)
{
	if(e == 0) return 1;
	LONGTYPE result;
	result = power(i, e/2);
	result *= result;
	if(e%2) result *= i;
	
	return result;
}

int main()
{
	ios::sync_with_stdio(false);
	fill_n(isprime, MAXEXP, true);
	for(int i = 2; i < MAXEXP; i++)
	{
		if(isprime[i])
			for(int j = 2*i; j < MAXEXP; j += i)
				isprime[j] = false;
	}
	results.reserve(67817);
	results.push_back(1);
	
	
	double lnMAX = log(pow(2.0, 64.0) - 1);
	for(int i = 2; i < 65536; i++)
	{
		int maxe = (int)(ceil(lnMAX/log(i)));
		for(int e = 4; e < maxe; e++)
		{
			if(!isprime[e])
			{
				LONGTYPE p = power(i, e);
				results.push_back(power(i, e));
			}
		}
	}
	
	sort(results.begin(), results.end());
	vector<LONGTYPE>::iterator iEnd = unique(results.begin(), results.end());
	for(vector<LONGTYPE>::iterator iter = results.begin(); iter != iEnd; iter++)
			cout<<(*iter)<<endl;
	
	return 0;
}

 
/* Ranking Submission Run Time Language Submission Date 
	88 		8455728 	0.144 	C++ 	2010-12-13 10:21:17  */

