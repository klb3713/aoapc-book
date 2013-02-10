// UVa11478 Halum
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int INF = 1000000000;
const int maxn = 500 + 10;
const int maxm = 2700 + 10;

struct Edge {
  int to, dist;
};

// 邻接表写法
struct BellmanFord {
  int n, m;
  Edge edges[maxm];
  int head[maxn];
  int next[maxm];
  bool inq[maxn];   // 是否在队列中
  int d[maxn];      // s到各个点的距离
  int cnt[maxn];    // 进队次数

  void init(int n) {
    this->n = n;
    m = 0;
    memset(head, -1, sizeof(head));
  }

  void AddEdge(int from, int to, int dist) {
    next[m] = head[from];
    head[from] = m;
    edges[m++] = (Edge){to, dist};
  }

  bool negativeCycle() {
    queue<int> Q;
    memset(inq, 0, sizeof(inq));
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < n; i++) { d[i] = 0; Q.push(i); }

    int u;
    while(!Q.empty()) {
      u = Q.front(); Q.pop();
      inq[u] = false;
      for(int i = head[u]; i != -1; i = next[i]) {
        Edge& e = edges[i];
        if(d[e.to] > d[u] + e.dist) {
          d[e.to] = d[u] + e.dist;
          if(!inq[e.to]) { Q.push(e.to); inq[e.to] = true; if(++cnt[e.to] > n) return true; }
        }
      }
    }
    return false;
  }
};

BellmanFord solver;

// 判断在初始差分约束系统的每个不等式右侧同时减去x之后是否有解
bool test(int x) {
  for(int i = 0; i < solver.m; i++)
    solver.edges[i].dist -= x;
  bool ret = solver.negativeCycle();
  for(int i = 0; i < solver.m; i++)
    solver.edges[i].dist += x;
  return !ret; // 如果有负环，说明差分约束系统无解
}

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2) {
    solver.init(n);
    int ub = 0;
    while(m--) {
      int u, v, d;
      scanf("%d%d%d", &u, &v, &d); ub = max(ub, d);
      solver.AddEdge(u-1, v-1, d);
    }

    if(test(ub+1)) printf("Infinite\n"); // 如果可以让每条边权都>ub，说明每条边的权都增加了，重复一次会增加得更多...直到无限
    else if(!test(1)) printf("No Solution\n");
    else {
      int L = 2, R = ub, ans = 1;
      while(L <= R) {
        int M = L + (R-L)/2;
        if(test(M)) { ans = M; L = M+1; } else R = M-1;
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
