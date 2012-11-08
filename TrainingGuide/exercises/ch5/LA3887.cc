// LA3887 Slim Span
// 陈锋
#include<cassert>
#include<cstdio>
#include<cstring>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
typedef vector<int> IntVector;
typedef vector<int>::iterator IntVectorIter;

struct Edge{
    int from, to, weight;
};

const int INF = 1000000000, MAXN = 100 + 1;
int n, m, SET[MAXN];
vector<Edge> edges;
IntVector edgeNums;

bool edgeComp(int i, int j) { return (edges[i].weight < edges[j].weight); }
int find(int x) { return SET[x] == x ? x : SET[x] = find(SET[x]); }

void runcase()
{    
    sort(edgeNums.begin(), edgeNums.end(), edgeComp);
    
    int result = INF;
    for(IntVectorIter minIt = edgeNums.begin(); minIt < edgeNums.end(); minIt++)
    {
        int minW = edges[*minIt].weight;
        int maxW = minW;
        // 假如it是最小边，求最小生成树
        for(int i = 0; i < n; i++)
            SET[i] = i;
        
        for(IntVectorIter it = minIt; it < edgeNums.end(); it++)
        {
            const Edge& e = edges[*it];
            int x = find(e.from);
            int y = find(e.to);
            if(x != y) { 
                SET[x] = y;
                maxW = e.weight;
            }
        }
        
        // 要判断最小生成树是否连通了
        bool connected = true;
        for(int i = 0; i < n; i++)
            if(find(i) != find(0))
            {
                connected = false;
                break;
            }
            
        if(connected)
            result = min(result, maxW - minW);
    }
    
    if(result == INF)
        result = -1;
    printf("%d\n", result);
}

int main() {
    while(true)
    {
        scanf("%d%d", &n, &m);
        if(n == 0) break;
        edges.clear();
        edgeNums.clear();
        
        
        for(int i = 0; i < m; i++)
        {
            int a, b, w;
            scanf("%d%d%d", &a, &b, &w);
            Edge e = {a - 1, b - 1, w};
            edges.push_back(e);
            edgeNums.push_back(i);
        }
        runcase();
    }
    return 0;
}