#include<stdio.h>
#include<string.h>
const int MAXN = 1000;
int n, m, G[MAXN][MAXN];
int c[MAXN];
int topo[MAXN], t;
bool dfs(int u){
  c[u] = -1;
  for(int v = 0; v < n; v++) if(G[u][v]) {
    if(c[v]<0) return false;
    else if(!c[v]) dfs(v);
  }
  c[u] = 1; topo[--t]=u;
  return true;
}

bool toposort(){
  t = n;
  memset(c, 0, sizeof(c));
  for(int u = 0; u < n; u++) if(!c[u])
    if(!dfs(u)) return false;
  return true;
}

int main() {
  scanf("%d%d", &n, &m);
  memset(G, 0, sizeof(G));
  for(int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    G[u][v] = 1;
  }
  if(toposort()) {
    for(int i = 0; i < n; i++)
      printf("%d\n", topo[i]);
  }
  else
    printf("No\n");
}
