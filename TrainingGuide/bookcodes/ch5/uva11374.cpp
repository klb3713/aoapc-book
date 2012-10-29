// UVa11374 Airport Express
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

const int INF = 1000000000;
const int maxn = 500 + 10;

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

  // dist[i]为s到i的距离，paths[i]为s到i的最短路径（经过的结点列表，包括s和t）
  void GetShortestPaths(int s, int* dist, vector<int>* paths) {
    dijkstra(s);
    for(int i = 0; i < n; i++) {
      dist[i] = d[i];
      paths[i].clear();
      int t = i;
      paths[i].push_back(t);
      while(t != s) {
        paths[i].push_back(edges[p[t]].from);
        t = edges[p[t]].from;
      }
      reverse(paths[i].begin(), paths[i].end());
    }
  }
};

//////// 题目相关
Dijkstra solver;
int d1[maxn], d2[maxn];
vector<int> paths1[maxn], paths2[maxn];

int main() {
  int kase = 0, N, S, E, M, K, X, Y, Z;
  while(scanf("%d%d%d%d", &N, &S, &E, &M) == 4) {
    solver.init(N);

    S--; E--; // 编号从0~N-1
    for(int i = 0; i < M; i++) {
      scanf("%d%d%d", &X, &Y, &Z); X--; Y--;
      solver.AddEdge(X, Y, Z);
      solver.AddEdge(Y, X, Z);
    }
    solver.GetShortestPaths(S, d1, paths1); // S到所有点的距离和路径
    solver.GetShortestPaths(E, d2, paths2); // T到所有点的距离和路径

    int ans = d1[E];              // 初始解解为直达距离
    vector<int> path = paths1[E]; // 初始解的station序列
    int midpoint = -1;            // 不坐商业线

    scanf("%d", &K);
    for(int i = 0; i < K; i++) {
      scanf("%d%d%d", &X, &Y, &Z); X--; Y--;
      for(int j = 0; j < 2; j++) { // j=0代表商业线坐X->Y，j=1代表Y->X
        if(d1[X] + d2[Y] + Z < ans) {
          ans = d1[X] + d2[Y] + Z;
          path = paths1[X];
          for(int j = paths2[Y].size()-1; j >= 0; j--) // 从Y到T的距离要反过来
            path.push_back(paths2[Y][j]);
          midpoint = X;
        }
        swap(X, Y);
      }
    }

    if(kase != 0) printf("\n");
    kase++;

    for(int i = 0; i < path.size()-1; i++) printf("%d ", path[i]+1);
    printf("%d\n", E+1);
    if(midpoint == -1) printf("Ticket Not Used\n"); else printf("%d\n", midpoint+1);
    printf("%d\n", ans);
  }
  return 0;
}
