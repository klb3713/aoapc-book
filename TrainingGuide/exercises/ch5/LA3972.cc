// LA3972 March of the Penguins
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

const int MAXN = 100 + 10, INF = 1000000000;

const double eps = 1e-6;

int dcmp(double x){
    if(fabs(x) < eps) return 0; 
    else return x < 0 ? -1 : 1;
}

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

Dinic<MAXN * 2> g;

struct Ice
{
    int x, y, n, m;
    void read()
    {
        scanf("%d%d%d%d", &x, &y, &n, &m);
    }
    double dist(const Ice& rhs)
    {
        return sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y));
    }
};

Ice iceData[MAXN];
int N;
double D, Dist[MAXN][MAXN];

bool tryMeet(int meet)
{
    g.ClearAll(2*N + 1);
    int s = 2 * N, t = 2 * meet, sum = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
            if(dcmp(Dist[i][j] - D) < 0)
                g.AddEdge(2*i + 1, 2*j, INF);
        
        const Ice& ice = iceData[i];
        sum += ice.n;
        g.AddEdge(2*i, 2*i + 1, ice.m);
        
        if(ice.n > 0)
            g.AddEdge(s, 2*i, ice.n);
    }
    
    int flow = g.Maxflow(s, t);
    return flow >= sum;
}

void runcase(int kase)
{
    scanf("%d%lf", &N, &D);
    int x, y, n, m;
    for(int i = 0; i < N; i++)
        iceData[i].read();
    vector<int> result;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
        {
            double &d = Dist[i][j];
            d = iceData[i].dist(iceData[j]);
        }
    
    for(int i = 0; i < N; i++)
    {
        // 尝试把 i 作为meet点
        if(tryMeet(i)) result.push_back(i);
    }
    
    if(result.empty())
    {
        puts("-1");
        return;
    }
    
    for(int i = 0; i < result.size(); i++)
    {
        if(i > 0) printf(" ");
        printf("%d", result[i]);
    }
    puts("");
}

int main() {
    int T;
    scanf("%d", &T);
    for(int t = 0; t < T; t++)
        runcase(t);
    return 0;
}