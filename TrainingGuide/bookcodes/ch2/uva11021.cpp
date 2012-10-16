// UVa11021 Tribbles
// Rujia Liu
#include<cstdio>
#include<cmath>
const int maxn = 1000 + 10;
const int maxm = 1000 + 10;
int n, k, m;
double P[maxn], f[maxm];
int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%d%d%d", &n, &k, &m);
    for(int i = 0; i < n; i++) scanf("%lf", &P[i]);
    f[0] = 0; f[1] = P[0];
    for(int i = 2; i <= m; i++) {
      f[i] = 0;
      for(int j = 0; j < n; j++) f[i] += P[j] * pow(f[i-1], j);
    }
    printf("Case #%d: %.7lf\n", kase, pow(f[m], k));
  }
  return 0;
}