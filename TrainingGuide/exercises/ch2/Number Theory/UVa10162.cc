// UVa10162 Last Digit
// ³Â·æ
#include <cstdio>
#include <cstring>
#include <algorithm>

int power_mod_10(int base, int power)
{
	if(power == 0) return 1;
	base %= 10;
	int x = power_mod_10(base, power/2);
	int result = x * x % 10;
	
	if(power % 2 == 1) result *= base;
	return result % 10;
}

int BUF[101];

int main()
{
	char N[128];
	int n;
	BUF[0] = 0;
	for(int i = 1; i < 101; i++)
		BUF[i] = ( BUF[i-1] + power_mod_10(i, i) ) % 10;
	
	while(true)
	{
		scanf("%s", N);
		if(N[0] == '0') break;
		
		int len = strlen(N);
		sscanf(N + (len >= 2 ? len - 2 : 0), "%d", &n);

		printf("%d\n", BUF[n]);
	}
}


