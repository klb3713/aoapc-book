// UVa10253 Series-Parallel Networks
// Rujia Liu
#include<cstdio>
#include<cstring>

long long C(long long n, long long m) {
  double ans = 1;
  for(int i = 0; i < m; i++)
    ans *= n-i;
  for(int i = 0; i < m; i++)
    ans /= i+1;
  return (long long)(ans + 0.5);
}

const int maxn = 30 + 5;
long long f[maxn], d[maxn][maxn]; //d(i,j)表示每棵树最多包含i个叶子，一共有j个叶子的方案数

int main() {
  f[1] = 1;
  memset(d, 0, sizeof(d));

  int n = 30;
  for(int i = 0; i <= n; i++) d[i][0] = 1;
  for(int i = 1; i <= n; i++) { d[i][1] = 1; d[0][i] = 0; }

  for(int i = 1; i <= n; i++) {
    for(int j = 2; j <= n; j++) {
      d[i][j] = 0;
      for(int p = 0; p*i <= j; p++)
        d[i][j] += C(f[i]+p-1, p) * d[i-1][j-p*i];
    }
    f[i+1] = d[i][i+1];
  }

  while(scanf("%d", &n) == 1 && n)
    printf("%lld\n", n == 1 ? 1 : 2*f[n]);
  return 0;
}
