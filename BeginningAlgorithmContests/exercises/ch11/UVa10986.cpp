// UVa10986 Sending email
// Rujia Liu
// 题意：给一个n个点m条边的无向图，从S到T的最短路长度
// 算法：dijkstra
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int INF = 1000000000;
const int maxn = 20000 + 10;

struct Edge {
  int from, to, dist;
  Edge(int u, int v, int d):from(u),to(v),dist(d) {}
};

struct HeapNode {
  int d, u;
  bool operator < (const HeapNode& rhs) const {
    return d > rhs.d;
  }
};

struct Dijkstra {
  int n, m;
  vector<Edge> edges;
  vector<int> G[maxn];
  bool done[maxn];    // 是否已永久标号
  int d[maxn];        // s到各个点的距离
  int p[maxn];        // 最短路中的上一条弧

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, int dist) {
    edges.push_back(Edge(from, to, dist));
    m = edges.size();
    G[from].push_back(m-1);
  }

  void dijkstra(int s) {
    priority_queue<HeapNode> Q;
    for(int i = 0; i < n; i++) d[i] = INF;
    d[s] = 0;
    memset(done, 0, sizeof(done));
    Q.push((HeapNode){0, s});
    while(!Q.empty()) {
      HeapNode x = Q.top(); Q.pop();
      int u = x.u;
      if(done[u]) continue;
      done[u] = true;
      for(int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if(d[e.to] > d[u] + e.dist) {
          d[e.to] = d[u] + e.dist;
          p[e.to] = G[u][i];
          Q.push((HeapNode){d[e.to], e.to});
        }
      }
    }
  }
};

//////// 题目相关
Dijkstra solver;

int main() {
  int T, kase = 0;
  scanf("%d", &T);
  while(T--) {
    int n, m, S, T, u, v, w;
    scanf("%d%d%d%d", &n, &m, &S, &T);
    solver.init(n);

    for(int i = 0; i < m; i++) {
      scanf("%d%d%d", &u, &v, &w);
      solver.AddEdge(u, v, w);
      solver.AddEdge(v, u, w);
    }
    solver.dijkstra(S);
    printf("Case #%d: ", ++kase);
    if(solver.d[T] < INF) printf("%d\n", solver.d[T]); else printf("unreachable\n");
  }
  return 0;
}
