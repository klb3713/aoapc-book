// UVa11248 Frequency Hopping：使用Dinic算法
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
  bool vis[maxn];         // BFS使用
  int d[maxn];           // 从起点到i的距离
  int cur[maxn];        // 当前弧指针

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

  vector<int> Mincut() { // call this after maxflow
    vector<int> ans;
    for(int i = 0; i < edges.size(); i++) {
      Edge& e = edges[i];
      if(vis[e.from] && !vis[e.to] && e.cap > 0) ans.push_back(i);
    }
    return ans;
  }

  void Reduce() {
    for(int i = 0; i < edges.size(); i++) edges[i].cap -= edges[i].flow;
  }
};

Dinic g;

int main() {
  int n, e, c, kase = 0;
  while(scanf("%d%d%d", &n, &e, &c) == 3 && n) {
    g.ClearAll(n);
    while(e--) {
      int b1, b2, fp;
      scanf("%d%d%d", &b1, &b2, &fp);
      g.AddEdge(b1-1, b2-1, fp);
    }
    int flow = g.Maxflow(0, n-1);
    printf("Case %d: ", ++kase);
    if(flow >= c) printf("possible\n");
    else {
      vector<int> cut = g.Mincut();
      g.Reduce();
      vector<Edge> ans;
      for(int i = 0; i < cut.size(); i++) {
        Edge& e = g.edges[cut[i]];
        e.cap = c;
        g.ClearFlow();
        if(flow + g.Maxflow(0, n-1) >= c) ans.push_back(e);
        e.cap = 0;
      }
      if(ans.empty()) printf("not possible\n");
      else {
        sort(ans.begin(), ans.end());
        printf("possible option:(%d,%d)", ans[0].from+1, ans[0].to+1);
        for(int i = 1; i < ans.size(); i++)
          printf(",(%d,%d)", ans[i].from+1, ans[i].to+1);
        printf("\n");
      }
    }
  }
  return 0;
}
