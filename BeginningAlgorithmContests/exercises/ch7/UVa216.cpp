// UVa216 Getting in Line
// Rujia Liu
// 题意：给平面上n(2<=n<=8)个点，把它们连成一条折线使得长度最短。每段线有固定的16个单位的附加长度
// 算法：枚举全排列
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int maxn = 10;
int n, x[maxn], y[maxn];

double calc(int* P, bool show=false) {
  double sum = 0;
  for(int i = 0; i < n-1; i++) {
    int x1 = x[P[i]], y1 = y[P[i]], x2 = x[P[i+1]], y2 = y[P[i+1]];
    double len = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)) + 16;
    if(show) printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2lf feet.\n", x1, y1, x2, y2, len);
    sum += len;
  }
  if(show) printf("Number of feet of cable required is %.2lf.\n", sum);
  return sum;
}

int main() {
  int P[maxn], bestP[maxn], kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    for(int i = 0; i < n; i++) { scanf("%d%d", &x[i], &y[i]); P[i] = i; }
    double ans = 1e30;
    do {
      double sum = calc(P);
      if(sum < ans) {
        ans = sum;
        memcpy(bestP, P, sizeof(P));
      }
    } while(next_permutation(P, P+n));
    printf("**********************************************************\n");
    printf("Network #%d\n", ++kase);
    calc(bestP, true);
  }
  return 0;
}
