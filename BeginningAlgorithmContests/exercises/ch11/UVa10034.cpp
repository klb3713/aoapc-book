// UVa10034 Freckles
// Rujia Liu
// 题意：输入平面上n个点，求最小生成树权值
// 算法：Kruskal算法
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 10;
int n;
double x[maxn], y[maxn];

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
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%lf%lf", &x[i], &y[i]);
    e.clear();
    for(int i = 0; i < n; i++)
      for(int j = i+1; j < n; j++) {
        double d = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
        e.push_back(Edge(i, j, d));
      }
    printf("%.2lf\n", MST());
    if(T) printf("\n");
  }
  return 0;
}
