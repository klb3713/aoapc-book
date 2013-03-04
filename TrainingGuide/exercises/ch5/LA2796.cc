// LA2796 Concert Hall Schedule
// 陈锋
#include<cstring>
#include<cstdio>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 365 + 2, INF = 1000000000;
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

MCMF<MAXN> solver;
int n;
void runcase() {
    int i, j, w, s, t;
    solver.init(MAXN);
    s = MAXN + 1; t = -1;
    
    for(int x = 0; x < n; x++)
    {
        scanf("%d %d %d", &i, &j, &w);
        
        solver.AddEdge(i, j + 1, 1, -w);
        s = min(s, i);
        t = max(t, j + 1);
    }
    
    s--;
    for(int x = s; x < t; x++)
        solver.AddEdge(x, x + 1, 2, 0);
        
    Int64 cost = solver.Mincost(s, t);
    printf("%lld\n", -cost);
}

int main() {
    while(scanf("%d", &n) == 1 && n > 0)
        runcase();
    return 0;
}