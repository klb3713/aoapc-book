// LA3882 And Then There Was One
// Rujia Liu
#include<cstdio>
const int maxn = 10000 + 2;
int f[maxn];

int main() {
  int n, k, m;
  while(scanf("%d%d%d", &n, &k, &m) == 3 && n) {
    f[1] = 0;
    for(int i = 2; i <= n; i++) f[i] = (f[i-1] + k) % i;
    int ans = (m - k + 1 + f[n]) % n;
    if (ans <= 0) ans += n;
    printf("%d\n", ans);
  }
  return 0;
}
