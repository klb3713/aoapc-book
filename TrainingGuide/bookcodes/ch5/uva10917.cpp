// UVa10917 A Walk through the Forest
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int INF = 1000000000;
const int maxn = 1000 + 10;

struct Edge {
  int from, to, dist;
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
    edges.push_back((Edge){from, to, dist});
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
int d[maxn]; // 到家距离

int dp(int u) {
  if(u == 1) return 1; // 到家了

  int& ans = d[u];
  if(ans >= 0) return ans;

  ans = 0;
  for(int i = 0; i < solver.G[u].size(); i++) {
    int v = solver.edges[solver.G[u][i]].to;
    if(solver.d[v] < solver.d[u]) ans += dp(v);
  }
  return ans;
}

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2) {
    solver.init(n);
    for(int i = 0; i < m; i++) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c); a--; b--;
      solver.AddEdge(a, b, c);
      solver.AddEdge(b, a, c);
    }

    solver.dijkstra(1); // 家(1)到所有点的距离。因为道路都是双向的，所以把家看作起点也行
    memset(d, -1, sizeof(d));
    printf("%d\n", dp(0)); // 办公室(0)到家的符合条件的路径条数
  }
  return 0;
}
