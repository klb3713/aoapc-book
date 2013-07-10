// UVa10746 Crime Wave - The Sequel
// Rujia Liu
// 题意：m个警察选n个去银行，使得到银行的平均时间最小。
// 算法：警察为点1~m，银行为点m+1~m+n，求点0到m+n+1的最小费用最大流
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

const int maxn = 40 + 10;
const int INF = 1000000000;

struct Edge {
  int from, to, cap, flow;
  double cost;
  Edge(int u, int v, int c, int f, double w):from(u),to(v),cap(c),flow(f),cost(w) {}
};

struct MCMF {
  int n, m;
  vector<Edge> edges;
  vector<int> G[maxn];
  int inq[maxn];         // 是否在队列中
  double d[maxn];        // Bellman-Ford
  int p[maxn];           // 上一条弧
  int a[maxn];           // 可改进量

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int cap, double cost) {
    edges.push_back(Edge(from, to, cap, 0, cost));
    edges.push_back(Edge(to, from, 0, 0, -cost));
    m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
  }

  bool BellmanFord(int s, int t, int& flow, double& cost) {
    for(int i = 0; i < n; i++) d[i] = INF;
    memset(inq, 0, sizeof(inq));
    d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

    queue<int> Q;
    Q.push(s);
    while(!Q.empty()) {
      int u = Q.front(); Q.pop();
      inq[u] = 0;
      for(int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
          d[e.to] = d[u] + e.cost;
          p[e.to] = G[u][i];
          a[e.to] = min(a[u], e.cap - e.flow);
          if(!inq[e.to]) { Q.push(e.to); inq[e.to] = 1; }
        }
      }
    }
    if(d[t] == INF) return false;
    flow += a[t];
    cost += d[t] * a[t];
    for(int u = t; u != s; u = edges[p[u]].from) {
      edges[p[u]].flow += a[t];
      edges[p[u]^1].flow -= a[t];
    }
    return true;
  }

  // 需要保证初始网络中没有负权圈
  int MincostMaxflow(int s, int t, double& cost) {
    int flow = 0; cost = 0;
    while(BellmanFord(s, t, flow, cost));
    return flow;
  }

};

MCMF g;

const int maxm = 5000 + 5;
int u[maxm], v[maxm], c[maxm];

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2 && n) {
    g.init(n+m+2);
    for(int i = 1; i <= n; i++)
      for(int j = 1; j <= m; j++) {
        double d;
        scanf("%lf", &d);
        g.AddEdge(j, m+i, 1, d);
      }
    for(int i = 1; i <= m; i++) g.AddEdge(0, i, 1, 0);
    for(int i = 1; i <= n; i++) g.AddEdge(m+i, m+n+1, 1, 0);
    double cost;
    int flow = g.MincostMaxflow(0, m+n+1, cost);
    printf("%.2lf\n", cost / n + 1e-8);
  }
  return 0;
}
