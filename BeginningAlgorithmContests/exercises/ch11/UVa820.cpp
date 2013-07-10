// UVa820 Internet Bandwidth
// Rujia Liu
// 题意：给一个无向网络，求最大流
// 算法：规模不大，用EdmondsKarp算法即可。
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 100 + 10;
const int INF = 1000000000;

struct Edge {
  int from, to, cap, flow;
  Edge(int u, int v, int c, int f):from(u),to(v),cap(c),flow(f) {}
};

struct EdmondsKarp {
  int n, m;
  vector<Edge> edges;    // 边数的两倍
  vector<int> G[maxn];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
  int a[maxn];           // 当起点到i的可改进量
  int p[maxn];           // 最短路树上p的入弧编号

  void init(int n) {
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int cap) {
    edges.push_back(Edge(from, to, cap, 0));
    edges.push_back(Edge(to, from, 0, 0));
    m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
  }

  int Maxflow(int s, int t) {
    int flow = 0;
    for(;;) {
      memset(a, 0, sizeof(a));
      queue<int> Q;
      Q.push(s);
      a[s] = INF;
      while(!Q.empty()) {
        int x = Q.front(); Q.pop();
        for(int i = 0; i < G[x].size(); i++) {
          Edge& e = edges[G[x][i]];
          if(!a[e.to] && e.cap > e.flow) {
            p[e.to] = G[x][i];
            a[e.to] = min(a[x], e.cap-e.flow);
            Q.push(e.to);
          }
        }
        if(a[t]) break;
      }
      if(!a[t]) break;
      for(int u = t; u != s; u = edges[p[u]].from) {
        edges[p[u]].flow += a[t];
        edges[p[u]^1].flow -= a[t];
      }
      flow += a[t];
    }
    return flow;
  }
};

EdmondsKarp g;

int main() {
  int n, m, s, t, kase = 0;
  while(scanf("%d%d%d%d", &n, &s, &t, &m) == 4 && n) {
    g.init(n);
    while(m--) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c); u--; v--;
      g.AddEdge(u, v, c);
      g.AddEdge(v, u, c);
    }
    printf("Network %d\nThe bandwidth is %d.\n\n", ++kase, g.Maxflow(s-1, t-1));
  }
  return 0;
}
