// UVa 10104  Euclid Problem
// ³Â·æ
#include <cstdio>
#include <cstring>
#include <algorithm>

void gcd(int a, int b, int& d, int& x, int& y)
{
	if(!b)
	{ 
		d = a; x = 1; y = 0;
	}
	else
	{
		gcd(b, a % b, d, y, x);
		y -= x * (a/b);
	}
}

int main()
{
	int a, b, d, x, y;
	while(scanf("%d%d", &a, &b) == 2)
	{
		gcd(a, b, d, x, y);
		printf("%d %d %d\n", x, y, d);
	}
	return 0;
}

/* Ranking Submission Run Time Language Submission Date 
130 	8454136 	0.116 	C++ 	2010-12-12 11:32:39  */