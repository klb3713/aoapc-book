// UVa10600 ACM Contest and Blackout
// 陈锋
#include<cassert>
#include<cstdio>
#include<cstring>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

struct Edge{
    int from, to, weight;
};

const int INF = 1000000000, MAXN = 100 + 1;
int N, M, SET[MAXN], WEIGHT[MAXN][MAXN], MAX_COST[MAXN][MAXN], pa[MAXN] /* 有根树 */;
vector<Edge> edges;
vector<int> edgeNums, MST[MAXN];

bool edgeComp(int i, int j) { return (edges[i].weight < edges[j].weight); }
int find(int x) { return SET[x] == x ? x : SET[x] = find(SET[x]); }
vector<int> dfsvis;

/*
    MST转成有根树
*/
void dfs(int u, int fa)
{
    if(fa != -1)
    {
        for(int i = 0; i < dfsvis.size(); i++)
        {
            int x = dfsvis[i];
            MAX_COST[x][u] = max(MAX_COST[x][fa], WEIGHT[u][fa]);
            MAX_COST[u][x] = MAX_COST[x][u];
        }
    }
    dfsvis.push_back(u);
    
    const vector<int>& adj = MST[u];
    for(int i = 0; i < adj.size(); i++)
    {
        int v = adj[i];
        if(v != fa) dfs(v, pa[v] = u);
    }
}

void runcase(int t)
{
    scanf("%d%d", &N, &M);
    edges.clear();
    edgeNums.clear();
    
    for(int i = 0; i < N; i++)
    {
        SET[i] = i;
        MST[i].clear();
    }
    
    for(int i = 0; i < M; i++)
    {
        int A, B, C;
        scanf("%d%d%d", &A, &B, &C);
        edges.push_back((Edge){A - 1, B - 1, C});
        edgeNums.push_back(i);
        WEIGHT[A - 1][B - 1] = C;
        WEIGHT[B - 1][A - 1] = C;
    }
    
    sort(edgeNums.begin(), edgeNums.end(), edgeComp);
    
    int ans = 0;
    set<int> mstEdges;
    for(vector<int>::iterator it = edgeNums.begin(); it != edgeNums.end(); it++)
    {
        const Edge& e = edges[*it];
        int x = find(e.from);
        int y = find(e.to);
        if(x != y) { 
            mstEdges.insert(*it);
            ans += e.weight; 
            SET[x] = y;
            MST[e.from].push_back(e.to);
            MST[e.to].push_back(e.from);
        }
    }
    printf("%d", ans);
    
    // 预处理maxcost[u][v]是“两点间在MST上的惟一路径上的最大权值”算法算出的矩阵
    // DFS把MST转换成有根树
    pa[0] = -1;
    memset(MAX_COST, sizeof(MAX_COST), 0);
    dfsvis.clear();
    dfs(0, -1);
    
    int ans2 = INF; // 次小生成树
    // 遍历不在MST里面的边u, v
    for(vector<int>::iterator it = edgeNums.begin(); it != edgeNums.end(); it++)
    {
        if(mstEdges.count(*it) > 0) continue;
        const Edge& e = edges[*it];       
        ans2 = min(ans2, ans + WEIGHT[e.from][e.to] - MAX_COST[e.from][e.to]);
    }
    printf(" %d\n", ans2);
}


int main() {
    int T;
    scanf("%d", &T);
    for(int t = 0; t < T; t++)
        runcase(t);
    return 0;
}