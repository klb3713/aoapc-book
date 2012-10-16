// UVa11762 Race To 1
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<cstring>

const int maxn = 1000000 + 10;
double f[maxn];
int removed[maxn], primes[maxn], vis[maxn];

void gen_primes(int n) {
  int p = 0;
  memset(removed, 0, sizeof(removed));
  for(int i = 2; i <= n; i++) if(!removed[i]) {
    primes[p++] = i;
    if(i <= n/i) for(int j = i*i; j <= n; j += i) removed[j] = 1;
  }
}

double dp(int x) {
  if(x == 1) return 0.0; // 边界
  if(vis[x]) return f[x]; // 记忆化
  vis[x] = 1;
  double& ans = f[x];
  int g = 0, p = 0; // 累加g(x)和p(x)
  ans = 0;
  for(int i = 0; primes[i] <= x; i++) {
    p++;
    if(x % primes[i] == 0) { g++; ans += dp(x / primes[i]); }
  }
  ans = (ans + p) / g;
  return ans;
}

int main() {
  int T;
  scanf("%d", &T);
  gen_primes(1000009);
  memset(vis, 0, sizeof(vis));
  for(int kase = 1; kase <= T; kase++) {
    int n;
    scanf("%d", &n);
    printf("Case %d: %.10lf\n", kase, dp(n));
  }
  return 0;
}
