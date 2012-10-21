// LA5713 Qin Shi Huang's National Road System
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 10;
int n, m, x[maxn], y[maxn], p[maxn];

int pa[maxn];
int findset(int x) { return pa[x] != x ? pa[x] = findset(pa[x]) : x; } 

vector<int> G[maxn];
vector<double> C[maxn];

struct Edge {
  int x, y;
  double d;
  bool operator < (const Edge& rhs) const {
    return d < rhs.d;
  }
};

Edge e[maxn*maxn];

double maxcost[maxn][maxn];
vector<int> nodes;

void dfs(int u, int fa, double facost) {
  for(int i = 0; i < nodes.size(); i++) {
    int x = nodes[i];
    maxcost[u][x] = maxcost[x][u] = max(maxcost[x][fa], facost);
  }
  nodes.push_back(u);
  for(int i = 0; i < G[u].size(); i++) {
    int v = G[u][i];
    if(v != fa) dfs(v, u, C[u][i]);
  }
}

double MST() {
  m = 0;
  for(int i = 0; i < n; i++)
    for(int j = i+1; j < n; j++)
      e[m++] = (Edge) { i, j, sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i] - y[j])*(y[i] - y[j])) };
  sort(e, e+m);
  for(int i = 0; i < n; i++) { pa[i] = i; G[i].clear(); C[i].clear(); }
  int cnt = 0;
  double ans = 0;
  for(int i = 0; i < m; i++) {
    int x = e[i].x, y = e[i].y, u = findset(x), v = findset(y);
    double d = e[i].d;
    if(u != v) {
      pa[u] = v;
      G[x].push_back(y); C[x].push_back(d);
      G[y].push_back(x); C[y].push_back(d);
      ans += d;
      if(++cnt == n-1) break;
    }
  }
  return ans;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d%d%d", &x[i], &y[i], &p[i]);
    double tot = MST();
    memset(maxcost, 0, sizeof(maxcost));
    nodes.clear();
    dfs(0, -1, 0);
    double ans = -1;
    for(int i = 0; i < n; i++)
      for(int j = i+1; j < n; j++) {
        ans = max(ans, (p[i] + p[j]) / (tot - maxcost[i][j]));
      }
   printf("%.2lf\n", ans);
  }
  return 0;
}
