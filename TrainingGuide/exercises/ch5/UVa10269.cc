// UVa10269 Adventure of Super Mario
// 陈锋
#include<cassert>
#include<cstdio>
#include<cstring>
#include<vector>
#include<set>
#include<queue>
#include<utility>
using namespace std;

const int INF = 1000000000, MAXN = 100 + 1, MAXK = 10 + 1;

struct Edge{
    int from, to, dist;
};

struct HeapNode{
    int d, u;
    bool operator < (const HeapNode& rhs) const {
        return d > rhs.d;
    }
};

template<int MAXSIZE>
struct Dijkstra{
    int n, m, d[MAXSIZE], p[MAXSIZE];
    vector<Edge> edges;
    vector<int> G[MAXSIZE];
    bool done[MAXSIZE];
    
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



int A, B, M, L, K, N;
struct Stat{ // 状态就是(location, power_left)，就是你在位置location，魔法鞋的使用次数还有power_left次。
    int location, power_left;
    void init(int s) { location = s / (K + 1), power_left = s % (K + 1); }
    
    Stat():location(0), power_left(K){}    
    int enc() const { return location * (K + 1) + power_left; }
};
vector<int> power_reach[MAXN];
vector<Edge> map[MAXN];
Dijkstra<MAXK * MAXN> stat_runner;
Stat stats[MAXK * MAXN];

void runcase(int t)
{
    vector<Edge> edges;
    Dijkstra<MAXN> pre_runner;
    scanf("%d%d%d%d%d", &A, &B, &M, &L, &K);
    N = A + B;
    for(int i = 0; i < N; i++)
        map[i].clear();
    
    for(int i = 0; i < M; i++)
    {
        int x, y, l;
        scanf("%d%d%d", &x, &y, &l);   
        Edge e1 = {x - 1, y - 1, l};
        Edge e2 = {y - 1, x - 1, l};
        map[x-1].push_back(e1);
        map[y-1].push_back(e2);
        edges.push_back(e1);
        edges.push_back(e2);
    }    
    
    // 预处理，算出从每个location出发，用一次魔法鞋能到达的所有location
    for(int loc = 0; loc < N; loc++)
    {
        pre_runner.init(N);
        // 构造一个图g，结点是输入的结点，边是所有村庄出发的边（因为不能经过城堡）以及loc出发的所有边
        for(vector<Edge>::iterator it = edges.begin(); it != edges.end(); it++)
            if(it->from < A || it->from == loc)
                pre_runner.addEdge(it->from, it->to, it->dist);
        
        // 从starting_location开始做一次dijkstra
        pre_runner.dijkstra(loc);
        
        power_reach[loc].clear();
        
        // 返回d值不超过L的所有点
        for(int i = 0; i < N; i++)
            if(pre_runner.d[i] <= L)
                power_reach[loc].push_back(i);
        
        // printf("pre(%d) ", loc);
        // for(int i = 0; i < power_reach[loc].size(); i++)
        // {
            // printf("%d ", power_reach[loc][i]);
        // }        
        // puts("");
    }  
    
    const int stat_cnt = N * (K + 1);
    stat_runner.init(stat_cnt);
    for(int i = 0; i < stat_cnt; i++)
    {
        Stat& s = stats[i];
        s.init(i);
        Stat newS;
        newS.power_left = s.power_left;
        // 有两种边，一种就是普通的沿着一条路走，location改变，power_left不变。
        vector<Edge>& edges = map[s.location];
        for(vector<Edge>::iterator it = edges.begin(); it != edges.end(); it++)
        {
            newS.location = it -> to;
            stat_runner.addEdge(i, newS.enc(), it -> dist);
        }
        
        // 还有一种就是用一次魔法鞋，location改变，power_left减1
        if(s.power_left > 0)
        {
            newS.power_left = s.power_left - 1;
            vector<int>& reach = power_reach[s.location];
            for(vector<int>::iterator it = reach.begin(); it != reach.end(); it++)
            {
                newS.location = *it;
                stat_runner.addEdge(i, newS.enc(), 0);
            }
        }
    }
    
    Stat s;
    s.location = N - 1;
    s.power_left = K;
    stat_runner.dijkstra(s.enc());
    
    int result = INF;
    for(int i = 0; i < stat_cnt; i++)
    {
        const Stat& s = stats[i];
        if(s.location == 0)
            result = min(result, stat_runner.d[i]);
    }
    
    printf("%d\n", result);
}


int main() {
    int T;
    scanf("%d", &T);
    for(int t = 0; t < T; t++)
        runcase(t);
    return 0;
}