#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define MAXN 1010
int n, G[MAXN][MAXN];
int x[MAXN], y[MAXN], d[MAXN];

int dp(int i) {
  int& ans = d[i];
  if(ans > 0) return ans;
  ans = 1;
  for(int j = 1; j <= n; j++) if(G[i][j]) ans = max(ans, dp(j)+1);
  return ans;
}

void print_ans(int i) {
  printf("%d ", i);
  for(int j = 1; j <= n; j++) if(G[i][j] && d[i] == d[j]+1) {
    print_ans(j);
    break;
  }
}

int main() {
  int i, j, ans, best;
  scanf("%d", &n);
  for(i = 1; i <= n; i++) {
    scanf("%d%d", &x[i], &y[i]);
    if(x[i] > y[i]) {
      int t = x[i]; x[i] = y[i]; y[i] = t;
    }
  }
  memset(G, 0, sizeof(G));
  for(i = 1; i <= n; i++)
    for(j = 1; j <= n; j++)
      if(x[i] < x[j] && y[i] < y[j]) G[i][j] = 1;

  ans = 0;
  for(i = 1; i <= n; i++)
    if(dp(i) > ans) {
      best = i;
      ans = dp(i);
    }
  printf("%d\n", ans);
  print_ans(best);
  printf("\n");
  return 0;
}
