#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int INF = 1000000000;
const int MAXN = 1000;

int n, m, s, t;
int a[MAXN], p[MAXN], cap[MAXN][MAXN], flow[MAXN][MAXN];

int main() {
  scanf("%d%d", &n, &m);
  memset(cap, 0, sizeof(cap));
  for(int i = 0; i < m; i++) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    cap[u][v] = c;
  }
  s = 0;
  t = n-1;
  int ans = 0;

  queue<int> q;
  memset(flow, 0, sizeof(flow));
  for(;;) {
    memset(a, 0, sizeof(a));
    a[s] = INF;
    q.push(s);
    while(!q.empty()) {
      int u = q.front(); q.pop();
      for(int v = 0; v < n; v++) if(!a[v] && cap[u][v]>flow[u][v]){
        p[v] = u; q.push(v);
        a[v] = min(a[u], cap[u][v]-flow[u][v]);
      }
    }
    if(a[t] == 0) break;
    for(int u = t; u != s; u = p[u]) {
      flow[p[u]][u] += a[t];
      flow[u][p[u]] -= a[t];
    }
    ans += a[t];
  }

  printf("%d\n", ans);
  return 0;
}
