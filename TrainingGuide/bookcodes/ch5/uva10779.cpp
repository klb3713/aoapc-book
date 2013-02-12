// UVa10779 Collector's Problem
// Rujia Liu
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
};

bool operator < (const Edge& a, const Edge& b) {
  return a.from < b.from || (a.from == b.from && a.to < b.to);
}

struct Dinic {
  int n, m, s, t;
  vector<Edge> edges;    // 边数的两倍
  vector<int> G[maxn];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
  bool vis[maxn];        // BFS使用
  int d[maxn];           // 从起点到i的距离
  int cur[maxn];         // 当前弧指针

  void ClearAll(int n) {
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void ClearFlow() {
    for(int i = 0; i < edges.size(); i++) edges[i].flow = 0;    
  }

  void AddEdge(int from, int to, int cap) {
    edges.push_back((Edge){from, to, cap, 0});
    edges.push_back((Edge){to, from, 0, 0});
    m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
  }

  bool BFS() {
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(s);
    vis[s] = 1;
    d[s] = 0;
    while(!Q.empty()) {
      int x = Q.front(); Q.pop();
      for(int i = 0; i < G[x].size(); i++) {
        Edge& e = edges[G[x][i]];
        if(!vis[e.to] && e.cap > e.flow) {
          vis[e.to] = 1;
          d[e.to] = d[x] + 1;
          Q.push(e.to);
        }
      }
    }
    return vis[t];
  }

  int DFS(int x, int a) {
    if(x == t || a == 0) return a;
    int flow = 0, f;
    for(int& i = cur[x]; i < G[x].size(); i++) {
      Edge& e = edges[G[x][i]];
      if(d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap-e.flow))) > 0) {
        e.flow += f;
        edges[G[x][i]^1].flow -= f;
        flow += f;
        a -= f;
        if(a == 0) break;
      }
    }
    return flow;
  }

  int Maxflow(int s, int t) {
    this->s = s; this->t = t;
    int flow = 0;
    while(BFS()) {
      memset(cur, 0, sizeof(cur));
      flow += DFS(s, INF);
    }
    return flow;
  }
};

Dinic g;

int main() {
  int T, n, m;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%d%d", &n, &m);
    g.ClearAll(n+m+1); // s=0, 物品为结点1~m, 除Bob外的人为结点m+1~m+n-1，t=m+n
    for(int i = 0; i < n; i++) {
      int k, kind;
      scanf("%d", &k);
      vector<int> cnt(m+1, 0);
      for(int j = 0; j < k; j++) { scanf("%d", &kind); cnt[kind]++; }
      if(i == 0) { // Bob
        for(int j = 1; j <= m; j++)
          if(cnt[j] >= 1) g.AddEdge(0, j, cnt[j]); // s连边到物品
      } else { // 其他人
        for(int j = 1; j <= m; j++) {
          if(cnt[j] >= 2) g.AddEdge(m+i, j, cnt[j]-1); // 此人可以给出cnt[j]-1个物品j
          else if(cnt[j] == 0) g.AddEdge(j, m+i, 1); // 此人可以接受1个物品j
        }
      }
    }
    for(int i = 1; i <= m; i++) g.AddEdge(i, m+n, 1);
    printf("Case #%d: %d\n", kase, g.Maxflow(0, m+n));
  }
  return 0;
}
