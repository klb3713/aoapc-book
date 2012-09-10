#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int INF = 1000000000;
const int MAXN = 1000;

int n, m, s, t;
int a[MAXN], d[MAXN], p[MAXN], cap[MAXN][MAXN], cost[MAXN][MAXN], flow[MAXN][MAXN];

int main() {
  scanf("%d%d", &n, &m);
  memset(cap, 0, sizeof(cap));
  memset(cost, 0, sizeof(cost));
  for(int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    scanf("%d%d", &cap[u][v], &cost[u][v]);
    cost[v][u] = -cost[u][v];
  }
  s = 0;
  t = n-1;
  int f = 0, c = 0;

  queue<int> q;
  int d[MAXN];
  memset(flow, 0, sizeof(flow));
  for(;;) {
    bool inq[MAXN];
    for(int i = 0; i < n; i++) d[i] = (i==s ? 0 : INF);
    memset(inq, 0, sizeof(inq));
    q.push(s);
    while(!q.empty()) {
      int u = q.front(); q.pop();
      inq[u] = false;
      for(int v = 0; v < n; v++) if(cap[u][v]>flow[u][v] && d[v]>d[u]+cost[u][v]) {
        d[v] = d[u] + cost[u][v];
        p[v] = u;
        if(!inq[v]) {
          inq[v] = true;
          q.push(v);
        }
      }
    }
    if(d[t] == INF) break;
    int a = INF;
    for(int u = t; u != s; u = p[u]) a = min(a, cap[p[u]][u] - flow[p[u]][u]);
    for(int u = t; u != s; u = p[u]) {
      flow[p[u]][u] += a;
      flow[u][p[u]] -= a;
    }
    c += d[t]*a;
    f += a;
  }

  printf("%d %d\n", f, c);
  return 0;
}
