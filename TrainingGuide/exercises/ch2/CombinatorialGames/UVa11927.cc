// UVa11927 Games Are Important
// 陈锋
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAXN = 1024;
vector<int> G[MAXN];
int sg[MAXN], vis[MAXN];
int n, m, end;

// 对于每个stone来说游戏是独立的，定义状态x为其所在的点的编号
int SG(int node)
{
    int& ans = sg[node];
    if(vis[node]) return ans;
    vector<int>& adj = G[node];
    vis[node] = 1;
    ans = 0;
    
    if(!adj.empty())
    {
        set<int> ints;
        for(vector<int>::iterator it = adj.begin(); it != adj.end(); it++)
            ints.insert(SG(*it));
        ans = 0;
        while(ints.count(ans))
            ans++;
    }
    
    return ans;
}

int main()
{
    while(true)
    {
        scanf("%d%d", &n, &m);
        if(n == 0) break;
               
        for(int i = 0; i < n; i++)
            G[i].clear();
        fill_n(sg, n + 1, 0);
        fill_n(vis, n + 1, 0);
        
        int a, b;
        for(int i = 0; i < m; i++)
        {
            scanf("%d%d", &a, &b);
            G[a].push_back(b);
        }
        
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            int s;
            scanf("%d", &s);
            if(s % 2) ans ^= SG(i);
        }
        
        puts(ans ? "First" : "Second");
    }
    
    return 0;    
}
