// LA4794 Sharing Chocolate
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 16;
const int maxw = 100 + 10;
int n, A[maxn], sum[1<<maxn], f[1<<maxn][maxw], vis[1<<maxn][maxw];

int bitcount(int x) { return x == 0 ? 0 : bitcount(x/2) + (x&1); }

int dp(int S, int x) {
  if(vis[S][x]) return f[S][x];
  vis[S][x] = 1;
  int& ans = f[S][x];
  if(bitcount(S) == 1) return ans = 1;
  int y = sum[S] / x;
  for(int S0 = (S-1)&S; S0; S0 = (S0-1)&S) {
    int S1 = S-S0;
    if(sum[S0]%x==0&&dp(S0,min(x,sum[S0]/x))&&dp(S1,min(x,sum[S1]/x))) return ans = 1;
    if(sum[S0]%y==0&&dp(S0,min(y,sum[S0]/y))&&dp(S1,min(y,sum[S1]/y))) return ans = 1;
  }
  return ans = 0;
}

int main() {
  int kase = 0, n, x, y;
  while(scanf("%d", &n) == 1 && n) {
    scanf("%d%d", &x, &y);
    for(int i = 0; i < n; i++) scanf("%d", &A[i]);

    // 每个子集中的元素之和
    memset(sum, 0, sizeof(sum));
    for(int S = 0; S < (1<<n); S++)
      for(int i = 0; i < n; i++) if(S & (1<<i)) sum[S] += A[i];

    memset(vis, 0, sizeof(vis));
    int ALL = (1<<n) - 1;
    int ans;
    if(sum[ALL] != x*y || sum[ALL] % x != 0) ans = 0;
    else ans = dp(ALL, min(x,y));
    printf("Case %d: %s\n", ++kase, ans ? "Yes" : "No");
  }
  return 0;
}
