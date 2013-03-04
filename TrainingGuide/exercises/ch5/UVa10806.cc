// UVa10806 Dijkstra, Dijkstra
// 陈锋
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

const int maxn = 100 + 10, INF = 1000000000;

typedef long long Int64;

struct Edge {
  int from, to, cap, flow, cost;
};

template<int MAXSIZE>
struct MCMF {
  int n, m;
  vector<Edge> edges;
  vector<int> G[MAXSIZE];
  bool inq[MAXSIZE];         // 是否在队列中
  int d[MAXSIZE];           // Bellman-Ford
  int p[MAXSIZE];           // 上一条弧
  int a[MAXSIZE];           // 可改进量

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

  bool BellmanFord(int s, int t, int &flow, Int64& ans) {
    fill_n(d, n, INF);
    fill_n(inq, n, false);
    d[s] = 0; inq[s] = true; p[s] = 0; a[s] = INF;

    queue<int> Q;
    Q.push(s);
    while(!Q.empty()) {
      int u = Q.front(); Q.pop();
      inq[u] = false;
      for(int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if(e.cap > e.flow && d[e.to] > d[u] + e.cost) {
          d[e.to] = d[u] + e.cost;
          p[e.to] = G[u][i];
          a[e.to] = min(a[u], e.cap - e.flow);
          if(!inq[e.to]) { Q.push(e.to); inq[e.to] = true; }
        }
      }
    }
    if(d[t] == INF) return false; //s-t 不连通，失败退出  
    flow += a[t];
    ans += (Int64)d[t] * (Int64)a[t];
    int u = t;
    while(u != s) {
      edges[p[u]].flow += a[t];
      edges[p[u]^1].flow -= a[t];
      u = edges[p[u]].from;      
    }
    return true;
  }

  // 需要保证初始网络中没有负权圈
  Int64 Mincost(int s, int t) {
    Int64 ans = 0;
    int flow = 0;
    while(BellmanFord(s, t, flow, ans));
    return ans;
  }
};

MCMF<maxn> solver;
int n;

void runcase()
{
    solver.init(n + 1);
    int m, from, to, cost;
    scanf("%d", &m);
    for(int i = 0; i < m; i++)
    {
        scanf("%d%d%d", &from, &to, &cost);
        solver.AddEdge(from, to, 1, cost);
        solver.AddEdge(to, from, 1, cost);
    }
    solver.AddEdge(0, 1, 2, 0);
        
    Int64 ans = solver.Mincost(0, n);
    int flow = solver.edges[solver.G[0].back()].flow;
    // printf("flow = %d, cost = %lld\n", flow, ans);
    
    if(flow != 2)
        puts("Back to jail");
    else
        printf("%lld\n", ans);
}

int main() {
    while(true)
    {
        scanf("%d", &n);
        if(n == 0) break;
        runcase();
    }
    return 0;
}