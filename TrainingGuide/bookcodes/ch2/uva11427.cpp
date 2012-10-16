// UVa11427 Expect the Expected
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<cstring>
const int maxn = 100 + 5;
int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    int n, a, b;
    double d[maxn][maxn], p;
    scanf("%d/%d%d", &a, &b, &n); // 请注意scanf的技巧
    p = (double)a/b;
    memset(d, 0, sizeof(d));
    d[0][0] = 1.0; d[0][1] = 0.0;
    for(int i = 1; i <= n; i++)
      for(int j = 0; j*b <= a*i; j++) { // 等价于枚举满足j/i <= a/b的j，但避免了误差
        d[i][j] = d[i-1][j]*(1-p);
        if(j) d[i][j] += d[i-1][j-1]*p;
      }
    double Q = 0.0;
    for(int j = 0; j*b <= a*n; j++) Q += d[n][j];
    printf("Case #%d: %d\n", kase, (int)(1/Q));
  }
  return 0;
}
