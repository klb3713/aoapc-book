#include<stdio.h>
#include<string.h>
const int MAXN = 1000;
int n, m, G[MAXN][MAXN], vis[MAXN][MAXN];

void euler(int u){
  for(int v = 0; v < n; v++) if(G[u][v] && !vis[u][v]) {
    vis[u][v] = vis[v][u] = 1;
    euler(v);
    printf("%d %d\n", u, v); // 打印的顺序是逆序的：最先打印的边实际上应该最后经过
  }
}

int main() {
  scanf("%d%d", &n, &m);
  memset(G, 0, sizeof(G));
  for(int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u][v] = G[v][u] = 1; // 无向图
  }
  euler(0);
}
