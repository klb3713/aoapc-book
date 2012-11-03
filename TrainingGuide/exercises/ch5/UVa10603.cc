// UVa10603    Fill
// 陈锋
#include <cassert>
#include<cstdio>
#include<cstring>
#include<vector>
#include<set>
#include<queue>
#include<utility>
using namespace std;
const int MAX = 200 + 1, MAXN = MAX * MAX, INF = 1000000000;
int A, B, C, D, BASE, n;

struct Edge{
    int from, to, dist;
};

struct HeapNode{
    int d, u;
    bool operator < (const HeapNode& rhs) const {
        return d > rhs.d;
    }
};

struct Dijkstra{
    int n, m, d[MAXN], p[MAXN];
    vector<Edge> edges;
    vector<int> G[MAXN];
    bool done[MAXN];
    
    void init(int n)
    {
        this->n = n;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
        m = 0;
    }
    
    void addEdge(int from, int to, int dist)
    {
        edges.push_back((Edge){from, to, dist});
        m = edges.size();        
        G[from].push_back(m - 1);
    }
    
    void dijkstra(int s)
    {
        priority_queue<HeapNode> Q;
        fill_n(d, n, INF);
        d[s] = 0;
        fill_n(done, n, false);
        Q.push((HeapNode){0, s});
        while(!Q.empty()) {
            HeapNode x = Q.top(); Q.pop();
            int u = x.u;
            if(done[u]) continue;
            done[u] = true;
            const vector<int>& adj = G[u];
            for(int i = 0; i < adj.size(); i++)
            {
                Edge& e = edges[adj[i]];
                int to = e.to;
                if(d[to] > d[u] + e.dist) {
                    d[to] = d[u] + e.dist;
                    p[to] = adj[i];
                    Q.push((HeapNode){d[to], to});
                }
            }
        }
    }
};

struct Stat{
    int a, b;
    void init(int u)
    {
        a = u / BASE, b = u % BASE;
    }
    
    Stat():a(0), b(0){}
    
    int enc() const { return a * BASE + b; }
    
    int isValid() const{
        return a >= 0 && b >= 0 && a <= A && b <= B && c() >= 0 && c() <= C;
    }
    
    int c() const {return C - a - b;}
};

Dijkstra runner;
vector<Stat> stats;
vector<bool> valid;
set< pair<int, int> > results;

void runcase(int t)
{
    scanf("%d%d%d%d", &A, &B, &C, &D);
    BASE = B + 1;
    n = (A + 1) * (B + 1);
    runner.init(n);
    
    for(int i = 0; i < n; i++)
    {
        Stat& s = stats[i];
        s.init(i);
        Stat newS;
        valid[i] = s.isValid();
        if(!valid[i]) continue;
        // 模拟倒水的过程
        int dist;
        
        // a->b
        dist = min(s.a, B - s.b);
        if(dist > 0)
        {
            newS.a = s.a - dist; 
            newS.b = s.b + dist;
            runner.addEdge(i, newS.enc(), dist);
        }
        
        // a->c
        dist = min(s.a, C - s.c());
        if(dist > 0)
        {
            newS.a = s.a - dist;
            newS.b = s.b;
            runner.addEdge(i, newS.enc(), dist);
        }
        
        // b->a
        dist = min(s.b, A - s.a);
        if(dist > 0)
        {
            newS.a = s.a + dist; 
            newS.b = s.b - dist;
            runner.addEdge(i, newS.enc(), dist);
        }
        
        // b->c
        dist = min(s.b, C - s.c());
        if(dist > 0)
        {
            newS.a = s.a;
            newS.b = s.b - dist;
            runner.addEdge(i, newS.enc(), dist);
        }
        
        // c->a
        dist = min(s.c(), A - s.a);
        if(dist > 0)
        {
            newS.a = s.a + dist;
            newS.b = s.b;
            runner.addEdge(i, newS.enc(), dist);
        }
        
        // c->b
        dist = min(s.c(), B - s.b);
        if(dist > 0)
        {
            newS.a = s.a;
            newS.b = s.b + dist;
            runner.addEdge(i, newS.enc(), dist);
        }
    }
    
    runner.dijkstra(0);
    
    int min_d = INF;
    
    results.clear();
    for(int i = 0; i < n; i++)
    {
        if(!valid[i]) continue;
        Stat& s = stats[i];
        int d = runner.d[i];
        int x = INF;
        if(s.a > 0 && s.a <= D)
            x = min(x, D - s.a);
        if(s.b > 0 && s.b <= D)
            x = min(x, D - s.b);
        int c = s.c();
        if(c > 0 && c <= D)
            x = min(x, D - c);
        
        results.insert(make_pair(x, d));
    }
    
    printf("%d %d\n", results.begin() -> second, D - results.begin() -> first);
}

int main() {
    int T;
    scanf("%d", &T);
    stats.reserve(MAXN);
    valid.reserve(MAXN);
    for(int t = 0; t < T; t++)
        runcase(t);
    return 0;
}