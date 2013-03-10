// UVa10491 Cows and Cars
// ³Â·æ
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int main()
{
	int cows, cars, show, all;
	double result;
	while(scanf("%d%d%d", &cows, &cars, &show) == 3)
	{
		all = cows + cars;
		result = (double)(cows * cars) / (all * (all - show - 1));
		result += (double)(cars * (cars - 1)) / (all * (all - show - 1));
		printf("%.5f\n", result);
	}

	return 0;
}
/* Ranking	Submission	Run Time	Language	Submission Date
	283		8482774		0.020		C++		2010-12-28 13:22:09 */
