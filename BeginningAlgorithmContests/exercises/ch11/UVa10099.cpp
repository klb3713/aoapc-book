// UVa10099 The Tourist Guide
// Rujia Liu
// 题意：输入一个无项带权图，有T个游客要从S点到D点。每条路有人数限制，而且每次都要有导游带。问至少要走几趟。本题没有重边。
// 算法：变形的floyd，先求出S到D最最大瓶颈路权值v，需要(T-1)/(v-1)+1次。
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;
int d[maxn][maxn];

int main() {
  int n, m, u, v, w, kase = 0;
  while(scanf("%d%d", &n, &m) == 2 && n) {
    // 初始化。直接看成完全图，不存在的边看成长度为0（而不是正无穷）
    memset(d, 0, sizeof(d));
    for(int i = 0; i < m; i++) {
      scanf("%d%d%d", &u, &v, &w); u--; v--;
      d[u][v] = d[v][u] = w;
    }
    // 主算法
    for(int k = 0; k < n; k++)
      for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
          d[i][j] = max(d[i][j], min(d[i][k], d[k][j]));

    int S, D, T;
    scanf("%d%d%d", &S, &D, &T);
    int v = d[S-1][D-1];
    printf("Scenario #%d\nMinimum Number of Trips = %d\n\n", ++kase, (T-1)/(v-1)+1);
  }
  return 0;
}
