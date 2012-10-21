// LA4128 Steam Roller：另一种构图法，得到的图较为复杂
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int INF = 1000000000;
const int maxn = 80000 + 10;

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

const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;

const int inv[] = {2, 3, 0, 1};
const int dr[] = {-1, 0, 1, 0}; // 上左下右
const int dc[] = {0, -1, 0, 1};
const int maxr = 100;
const int maxc = 100;

int grid[maxr][maxc][4];

int n, id[maxr][maxc][4][2];

int ID(int r, int c, int dir, int doubled) {
  int& x = id[r][c][dir][doubled];
  if(x == 0) x = ++n; // 从1开始编号
  return x;
}

int readint() {
  int x;
  scanf("%d", &x);
  return x;
}

int R, C;

bool cango(int r, int c, int dir) {
  if(r < 0 || r >= R || c < 0 || c >= C) return false; // 走出网格
  return grid[r][c][dir] > 0; // 此路不通？
}

Dijkstra solver;

int main() {
  int r1, c1, r2, c2, kase = 0;
  while(scanf("%d%d%d%d%d%d", &R, &C, &r1, &c1, &r2, &c2) == 6 && R) {
    r1--; c1--; r2--; c2--;
    for(int r = 0; r < R; r++) {
      for(int c = 0; c < C-1; c++)
        grid[r][c][RIGHT] = grid[r][c+1][LEFT] = readint();
      if(r != R-1) for(int c = 0; c < C; c++)
        grid[r][c][DOWN] = grid[r+1][c][UP] = readint();
    }
    solver.init(R*C*8+1);

    n = 0;
    memset(id, 0, sizeof(id));

    // 源点出发的边
    for(int dir = 0; dir < 4; dir++) if(cango(r1, c1, dir))
       solver.AddEdge(0, ID(r1+dr[dir], c1+dc[dir], dir, 1), grid[r1][c1][dir]*2);

    // 计算每个状态(r,c,dir,doubled)的后继状态
    for(int r = 0; r < R; r++)
      for(int c = 0; c < C; c++)
        for(int dir = 0; dir < 4; dir++) if(cango(r, c, inv[dir]))
          for(int newdir = 0; newdir < 4; newdir++) if(cango(r, c, newdir))
            for(int doubled = 0; doubled < 2; doubled++) {
              int newr = r + dr[newdir];
              int newc = c + dc[newdir];
              int v = grid[r][c][newdir], newdoubled = 0;
              if(dir != newdir) {
                if(!doubled) v += grid[r][c][inv[dir]]; // 上条边加倍
                newdoubled = 1; v += grid[r][c][newdir]; // 本条边加倍
              }
              solver.AddEdge(ID(r, c, dir, doubled), ID(newr, newc, newdir, newdoubled), v);
            }

    // 跑dijkstra
    solver.dijkstra(0);

    // 找最优解
    int ans = INF;
    for(int dir = 0; dir < 4; dir++) if(cango(r2, c2, inv[dir])) 
      for(int doubled = 0; doubled < 2; doubled++) {
        int v = solver.d[ID(r2, c2, dir, doubled)];
        if(!doubled) v += grid[r2][c2][inv[dir]];
        ans = min(ans, v);
      }

    printf("Case %d: ", ++kase);
    if(ans == INF) printf("Impossible\n"); else printf("%d\n", ans);
  }
  return 0;
}
