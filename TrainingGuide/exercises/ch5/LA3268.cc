// LA3268 Jamie's Contact Group
// 陈锋
#include<cstdio>
#include<cstring>
#include<iostream>
#include<sstream>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = 1000 + 10, MAXM = 500 + 10, INF = 1000000000;

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

Dinic<MAXN + MAXM> g;
int N, M;
string line, name;
void runcase(int kase)
{
    const int s = N + M, t = N + M + 1;
    g.ClearAll(t + 1);
    getline(cin, line);
    for(int i = 0; i < N; i++)
    {
        g.AddEdge(s, i, 1);
        getline(cin, line);
        istringstream iss(line);
        iss>>name;
        int grp;
        while(iss>>grp)
            g.AddEdge(i, N + grp, 1);
    }
    
    for(int i = 0; i < M; i++)
        g.AddEdge(N + i, t, 0);
        
    int LOW = 0, HIGH = N + 1;
    
    int ans = -1;
    while(LOW < HIGH)
    {        
        int mid = (HIGH + LOW) / 2;
        g.ClearFlow();
        for(int i = 0; i < M; i++)
        {
            Edge& e = g.edges[g.G[N + i].back()];
            e.cap = mid;
        }
        
        int f = g.Maxflow(s, t);
        bool ok = (f >= N);
        
        if(ok)
        {
            ans = -1;
            for(int i = 0; i < M; i++)
            {
                Edge& e = g.edges[g.G[N + i].back()];
                ans = max(ans, e.flow);
            }
        }
        
        if(ok)
            HIGH = mid;
        else
            LOW = mid + 1;
    }
    
    cout<<ans<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int kase = 1;
    while(true)
    {
        cin>>N>>M;
        if(N == 0) break;
        runcase(kase++);
    }
    return 0;
}