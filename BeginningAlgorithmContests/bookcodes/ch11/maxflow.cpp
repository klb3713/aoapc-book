#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
const int MAXN = 1000;

int n, m, s, t;
int vis[MAXN], p[MAXN], cap[MAXN][MAXN], flow[MAXN][MAXN];

int path(int u){
  int d;
  vis[u] = 1;
  if(u == t) return INF;
  else for(int v = 0; v < n; v++)
    if(!vis[v] && cap[u][v]>flow[u][v] && (d = path(v)) > 0){
      p[v] = u;
      return min(d, cap[u][v]-flow[u][v]);
  }
  return 0;
}

int main() {
  scanf("%d%d", &n, &m);
  memset(cap, 0, sizeof(cap));
  memset(flow, 0, sizeof(flow));
  for(int i = 0; i < m; i++) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    cap[u][v] = c;
  }
  s = 0;
  t = n-1;
  int ans = 0;
  for(;;) {
    memset(vis, 0, sizeof(vis));
    int d = path(s);
    if(d == 0) break;
    for(int u = t; u != s; u = p[u]) {
      flow[p[u]][u] += d;
      flow[u][p[u]] -= d;
    };
    ans += d;
  }
  printf("%d\n", ans);
  return 0;
}
