// UVa590 Always on the run
// Rujia Liu
// 题意：有n个城市，每两个城市之间的航线都是周期性的。某人想从城市1出发，恰好乘k次飞机之后到达城市n，求最小开销。
// 算法：动态规划。设d[i][j]为坐i次飞机以后到达城市j的最小开销，用刷表法比较好写。
#include<cstdio>
#include<cstring>
const int maxn = 10;
const int maxk = 1000 + 5;
const int maxd = 30;
int n, k, len[maxn][maxn], cost[maxn][maxn][maxd], d[maxk][maxn];

int main() {
  int kase = 0;
  while(scanf("%d%d", &n, &k) == 2 && n) {
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++) if(i != j) {
        scanf("%d", &len[i][j]);
        for(int a = 0; a < len[i][j]; a++) scanf("%d", &cost[i][j][a]);
      }
    memset(d, -1, sizeof(d));
    d[0][0] = 0;
    for(int i = 0; i < k; i++)
      for(int j = 0; j < n; j++) if(d[i][j] >= 0)
        for(int p = 0; p < n; p++) if(j != p) {
          int c = cost[j][p][i % len[j][p]], v = d[i][j] + c;
          if(c > 0 && (d[i+1][p] < 0 || v < d[i+1][p])) d[i+1][p] = v;
        }

    printf("Scenario #%d\n", ++kase);
    int ans = d[k][n-1];
    if(ans < 0) printf("No flight possible.\n");
    else printf("The best flight costs %d.\n", ans);
    printf("\n");
  }
  return 0;
}
