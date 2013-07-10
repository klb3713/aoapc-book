// UVa10397 Connect the Campus
// Rujia Liu
// 题意：输入平面上n个点，已经有m对点连起来。要求把所有点连起来，问至少还要连多长的距离
// 算法：把边长设为0，然后用Kruskal算法
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 10;
int n, x[maxn], y[maxn];

int pa[maxn];
int findset(int x) { return pa[x] != x ? pa[x] = findset(pa[x]) : x; } 

struct Edge {
  int u, v;
  double d;
  Edge(int u, int v, double d):u(u),v(v),d(d) {}
  bool operator < (const Edge& rhs) const {
    return d < rhs.d;
  }
};

vector<Edge> e;

double MST() {
  int m = e.size();
  sort(e.begin(), e.end());
  for(int i = 0; i < n; i++) pa[i] = i;
  int cnt = 0;
  double ans = 0;
  for(int i = 0; i < m; i++) {
    int u = findset(e[i].u), v = findset(e[i].v);
    double d = e[i].d;
    if(u != v) {
      pa[u] = v;
      ans += d;
      if(++cnt == n-1) break;
    }
  }
  return ans;
}

int main() {
  while(scanf("%d", &n) == 1) {
    for(int i = 0; i < n; i++) scanf("%d%d", &x[i], &y[i]);
    e.clear();
    for(int i = 0; i < n; i++)
      for(int j = i+1; j < n; j++) {
        double d = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
        e.push_back(Edge(i, j, d));
      }
    int k, u, v;
    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
      scanf("%d%d", &u, &v);
      e.push_back(Edge(u-1, v-1, 0));
    }
    printf("%.2lf\n", MST());
  }
  return 0;
}
