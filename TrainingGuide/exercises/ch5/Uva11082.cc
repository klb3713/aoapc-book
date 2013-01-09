// UVa11082 Matrix Decompressing
// 陈锋
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>
#include<set>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXR = 20 + 1, MAXE = 20, INF = 1000000000;

struct Edge {
  int from, to, cap, flow;
};

bool operator < (const Edge& a, const Edge& b) {
  return a.from < b.from || (a.from == b.from && a.to < b.to);
}

template<int MAXSIZE>
struct Dinic {
  int n, m, s, t;
  vector<Edge> edges;    // 边数的两倍
  vector<int> G[MAXSIZE];   // 邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
  bool vis[MAXSIZE];         // BFS使用
  int d[MAXSIZE];           // 从起点到i的距离
  int cur[MAXSIZE];        // 当前弧指针

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
};

Dinic<2*MAXR> g;
int R, C, CUM_R[MAXR], CUM_C[MAXR], SUM_R[MAXR], SUM_C[MAXR];

void runcase(int kase)
{
    printf("Matrix %d\n", kase);
    scanf("%d%d", &R, &C);

    g.ClearAll(R + C + 2);    
    int s = R + C, t = R + C + 1;
    for(int i = 0; i < R; i++)
    {
        scanf("%d", CUM_R + i);
        int &d = SUM_R[i];
        d = CUM_R[i];
        if(i > 0) d -= CUM_R[i-1];
        
        g.AddEdge(s, i, d - C);
        for(int j = 0; j < C; j++)
            g.AddEdge(i, R + j, MAXE - 1);
    }
    
    for(int i = 0; i < C; i++)
    {
        scanf("%d", CUM_C + i);
        int &d = SUM_C[i];
        d = CUM_C[i];
        if(i > 0) d -= CUM_C[i - 1];
        g.AddEdge(R + i, t, d - R);
    }
    
    int flow = g.Maxflow(s, t);
    for(int i = 0; i < R; i++)
    {
        const vector<int>& ens = g.G[i];
        bool first = true;
        for(int j = 0; j < ens.size(); j++)
        {
            const Edge& e = g.edges[ens[j]];
            if(e.cap != 0)
            {
                if(first) 
                    first = false;
                else 
                    printf(" ");
                printf("%d", e.flow + 1);
            }
        }
        puts("");
    }
    puts("");
}

int main() {
    int T;
    scanf("%d", &T);
    for(int t = 1; t <= T; t++)
        runcase(t);
    return 0;
}