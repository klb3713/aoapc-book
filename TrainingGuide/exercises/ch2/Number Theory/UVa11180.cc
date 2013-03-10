// UVa11180 Base i-1
// ³Â·æ
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

void print(int a, int b)
{
	if(a == 0 && b == 0)
		printf("0");
	else if(a == 1 && b == 0)
		printf("1");
	else if((a+b)%2)
	{
		print((b-a+1)/2, (-a+1-b)/2);		
		printf("1");
	}
	else
	{		
		print((b-a)/2, (-a-b)/2);
		printf("0");
	}
}

int main()
{
	int n = 0, N;
	scanf("%d", &N);
	while(n < N)
	{
		int a, b;
		scanf("%d%d", &a, &b);

		printf("Case #%d: ", ++n);
		print(a, b);
		puts("");
	}
	return 0;
}

//Ranking	Submission	Run Time	Language	Submission Date
//	16		8480613		0.032		C++			2010-12-27 01:50:33