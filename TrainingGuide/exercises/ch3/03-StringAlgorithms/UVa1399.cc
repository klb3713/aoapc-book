// LA3907 Puzzle(UVa 1399)
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <set>

using namespace std;

int readint()
{
    int x;
    scanf("%d", &x);
    return x;
}

template <int MAXNODE, int SIGMA_SIZE>
struct AhoCorasickAutomata {
  int ch[MAXNODE][SIGMA_SIZE];
  int f[MAXNODE];    // fail函数
  int match[MAXNODE];  // 是否包含某一个字符串
  int sz;            // 结点总数

  void init() {
    sz = 1;
    memset(ch[0], 0, sizeof(ch[0]));
  }
  
  // 插入字符串
  void insert(char *s) {
    int u = 0, n = strlen(s);
    for(int i = 0; i < n; i++) {
      int c = s[i] - 'A';
      if(!ch[u][c]) {
        memset(ch[sz], 0, sizeof(ch[sz]));
        match[sz] = 0;
        ch[u][c] = sz++;
      }
      u = ch[u][c];
    }
    match[u] = 1;
  }

  // 计算fail函数
  void getFail() {
    queue<int> q;
    f[0] = 0;
    // 初始化队列
    for(int c = 0; c < SIGMA_SIZE; c++) {
      int u = ch[0][c];
      if(u) { f[u] = 0; q.push(u); }
    }
    // 按BFS顺序计算fail
    while(!q.empty()) {
      int r = q.front(); q.pop();
      for(int c = 0; c < SIGMA_SIZE; c++) {
        int u = ch[r][c];
        if(!u) { ch[r][c] = ch[f[r]][c]; continue; }
        q.push(u);
        int v = f[r];
        while(v && !ch[v][c]) v = f[v];
        f[u] = ch[v][c];
        match[u] |= match[f[u]];
      }
    }
  }

  void dump() {
    printf("sz = %d\n", sz);
    for(int i = 0; i < sz; i++)
    {
        printf("%d -> match(%d) { ", i, match[i]);
        for(int j = 0; j < SIGMA_SIZE; j++)
        {
            if(ch[i][j] && !match[ch[i][j]]) printf("%d, ", ch[i][j]);
        }
        puts(" }");
    }
    printf("\n");
  }
};

const int maxn = 1000000 + 10, max_s = 26;

vector<int> G[maxn];
AhoCorasickAutomata<maxn, max_s> ac;
char buf[64];
int vis[maxn], d[maxn], pa[maxn];

bool dfs(int i)
{
    int& v = vis[i];
    if(v == 1) return true;
    if(v == -1) return false;
    
    v = -1;
    vector<int>& g = G[i];
    for(int j = 0; j < g.size(); j++)
        if(!dfs(g[j])) return false;
    
    v = 1;
    return true;
}

int dp(int i)
{
    int& v = vis[i];
    int& ans = d[i];
    if(v) return ans;
    v = 1;
    ans = 0;
    
    vector<int>& g = G[i];
    for(int j = 0; j < g.size(); j++)
        ans = max(ans, dp(g[j]) + 1);
    
    return ans;
}

void solve()
{
    ac.init();
    int n = readint(), s = readint();
    for(int i = 0; i < s; i++)
    {
        scanf("%s", buf);
        ac.insert(buf);
    }
    ac.getFail();
    // ac.dump();
    
    fill_n(vis, ac.sz, 0);
    for(int i = 0; i < ac.sz; i++)
    {
        vector<int>& v = G[i];
        v.clear();        
        if(!ac.match[i])
        {      
            int adj;
            for(int j = 0; j < n; j++)
            {
                adj = ac.ch[i][j];
                if(!ac.match[adj])
                    v.push_back(adj);
            }
        }
    }
    if(!dfs(0))  { puts("No"); return; } // 判圈
    
    fill_n(vis, ac.sz, 0);
    
    int u = 0;
    string str;
    while(dp(u))
    {
        // printf("u == %d, d = %d\n", u, dp(u));
        for(int j = n-1; j >= 0; --j)
        {
            int x = ac.ch[u][j];
            if(x && !ac.match[x] && dp(x) + 1 == dp(u))
            {
                str.push_back(j + 'A');
                u = x;
                break;
            }
        }
    }
    if(str.empty()) puts("No"); else puts(str.c_str());
}

int main()
{
    int T = readint();
    for(int i = 0; i < T; i++)
    {
        solve();
    }
    
    return 0;
}
