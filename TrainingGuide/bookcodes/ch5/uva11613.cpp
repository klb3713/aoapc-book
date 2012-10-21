// UVa11613 Acme Corporation
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

const int maxn = 202 + 10;
const int INF = 1000000000;

typedef long long LL;

struct Edge {
  int from, to, cap, flow, cost;
};

struct MCMF {
  int n, m, s, t;
  vector<Edge> edges;
  vector<int> G[maxn];
  int inq[maxn];         // 是否在队列中
  int d[maxn];           // Bellman-Ford
  int p[maxn];           // 上一条弧
  int a[maxn];           // 可改进量

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int cap, int cost) {
    edges.push_back((Edge){from, to, cap, 0, cost});
    edges.push_back((Edge){to, from, 0, 0, -cost});
    m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
  }

  bool BellmanFord(int s, int t, LL& ans) {
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
    if(d[t] > 0) return false;
    ans += (LL)d[t] * (LL)a[t];
    int u = t;
    while(u != s) {
      edges[p[u]].flow += a[t];
      edges[p[u]^1].flow -= a[t];
      u = edges[p[u]].from;      
    }
    return true;
  }

  // 需要保证初始网络中没有负权圈
  LL Mincost(int s, int t) {
    LL cost = 0;
    while(BellmanFord(s, t, cost));
    return cost;
  }

};

MCMF g;

int main() {
  int T, month, store_cost;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%d%d", &month, &store_cost);
    g.init(2*month+2);
    int source = 0, sink = 2*month+1;
    for(int i = 1; i <= month; i++) {
      int make_cost, make_limit, price, sell_limit, max_store;
      scanf("%d%d%d%d%d", &make_cost, &make_limit, &price, &sell_limit, &max_store);
      g.AddEdge(source, i, make_limit, make_cost);
      g.AddEdge(month+i, sink, sell_limit, -price); // 收益是负费用
      for(int j = 0; j <= max_store; j++) if(i + j <= month)
        g.AddEdge(i, month+i+j, INF, store_cost * j); // 存j个月以后卖
    }
    printf("Case %d: %lld\n", kase, -g.Mincost(source, sink));
  }
  return 0;
}
