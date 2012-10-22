// LA3661 Animal Run：每个三角形一个结点
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
const int maxn = 2000000 + 10;

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
#define REP(i,n) for(int i = 0; i < (n); ++i)

int n, m;
int ID(int r, int c, int half) { return half * n * m + r * m + c + 1; }

const int maxsize = 1000;
int cost[maxsize][maxsize][3];

Dijkstra solver;

int main() {
  int kase = 0;
  while(scanf("%d%d", &n, &m) == 2 && n && m) {
    REP(i,n) REP(j,m-1) scanf("%d", &cost[i][j][0]); // 横线
    REP(i,n-1) REP(j,m) scanf("%d", &cost[i][j][1]); // 竖线
    REP(i,n-1) REP(j,m-1) scanf("%d", &cost[i][j][2]); // 斜线
    solver.init(2*n*m+2);
    REP(i,n-1) REP(j,m-1) {
      // 左下half=0
      int id1 = ID(i, j, 0);
      if(j > 0) solver.AddEdge(id1, ID(i, j-1, 1), cost[i][j][1]); // 左
      if(i < n-1) solver.AddEdge(id1, ID(i+1, j, 1), cost[i+1][j][0]); // 下

      // 右上half=1
      int id2 = ID(i, j, 1);
      if(j < m-1) solver.AddEdge(id2, ID(i, j+1, 0), cost[i][j+1][1]); // 右
      if(i > 0) solver.AddEdge(id2, ID(i-1, j, 0), cost[i][j][0]); // 上

      solver.AddEdge(id1, id2, cost[i][j][2]);
      solver.AddEdge(id2, id1, cost[i][j][2]);
    }
    // 从起点到左/下边界的弧
    REP(i, n-1) solver.AddEdge(0, ID(i, 0, 0), cost[i][0][1]); // 左
    REP(i, m-1) solver.AddEdge(0, ID(n-2, i, 0), cost[n-1][i][0]); // 下

    // 从右/上边界到终点的弧
    REP(i, n-1) solver.AddEdge(ID(i, m-2, 1), 2*n*m+1, cost[i][m-1][1]); // 右
    REP(i, m-1) solver.AddEdge(ID(0, i, 1), 2*n*m+1, cost[0][i][0]); // 上
    solver.dijkstra(0);

    // 找出右/上边界的最少d值
    printf("Case %d: Minimum = %d\n", ++kase, solver.d[2*n*m+1]);
  }
  return 0;
}
