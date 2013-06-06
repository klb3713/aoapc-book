// UVa10004 Bicoloring
// Rujia Liu
// 题意：给一个无向图，判断是否能二着色
#include<cstdio>
#include<cstring>
const int maxn = 200 + 5;
int n, m, G[maxn][maxn], c[maxn];

bool dfs(int u, int color) {
  c[u] = color;
  for(int v = 0; v < n; v++) if(G[u][v]) {
    if(c[v] == color) return false;
    else if(!c[v]) dfs(v, 3-color);
  }
  return true;
}

bool bipartite() {
  memset(c, 0, sizeof(c));
  for(int u = 0; u < n; u++) if(!c[u]) {
    if(!dfs(u, 1)) return false;
  }
  return true;
}

int main() {
  while(scanf("%d%d", &n, &m) == 2 && n) {
    memset(G, 0, sizeof(G));
    for(int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      G[u][v] = G[v][u] = 1;
    }
    if(!bipartite()) printf("NOT ");
    printf("BICOLORABLE.\n");
  }
  return 0;
}
