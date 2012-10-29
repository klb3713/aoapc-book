// UVa11324 The Largest Clique
// Rujia Liu
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<stack>
using namespace std;

const int maxn = 1000 + 10;

vector<int> G[maxn];
int pre[maxn], lowlink[maxn], sccno[maxn], dfs_clock, scc_cnt;
stack<int> S;

void dfs(int u) {
  pre[u] = lowlink[u] = ++dfs_clock;
  S.push(u);
  for(int i = 0; i < G[u].size(); i++) {
    int v = G[u][i];
    if(!pre[v]) {
      dfs(v);
      lowlink[u] = min(lowlink[u], lowlink[v]);
    } else if(!sccno[v]) {
      lowlink[u] = min(lowlink[u], pre[v]);
    }
  }
  if(lowlink[u] == pre[u]) {
    scc_cnt++;
    for(;;) {
      int x = S.top(); S.pop();
      sccno[x] = scc_cnt;
      if(x == u) break;
    }
  }
}

void find_scc(int n) {
  dfs_clock = scc_cnt = 0;
  memset(sccno, 0, sizeof(sccno));
  memset(pre, 0, sizeof(pre));
  for(int i = 0; i < n; i++)
    if(!pre[i]) dfs(i);
}

int size[maxn], TG[maxn][maxn];
int d[maxn];
int dp(int u) {
  int& ans = d[u];
  if(ans >= 0) return ans;
  ans = size[u];
  for(int v = 1; v <= scc_cnt; v++)
    if(u != v && TG[u][v]) ans = max(ans, dp(v) + size[u]);
  return ans;
}

int main() {
  int T, n, m;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) G[i].clear();
    for(int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v); u--; v--;
      G[u].push_back(v);
    }

    find_scc(n); // 找强连通分量

    memset(TG, 0, sizeof(TG));
    memset(size, 0, sizeof(size));
    for(int i = 0; i < n; i++) {
      size[sccno[i]]++; // 累加强连通分量大小（结点数）
      for(int j = 0; j < G[i].size(); j++)
        TG[sccno[i]][sccno[G[i][j]]] = 1; // 构造SCC图
    }

    int ans = 0;
    memset(d, -1, sizeof(d)); // 初始化动态规划记忆化数组
    for(int i = 1; i <= scc_cnt; i++) // 注意，SCC编号为1~scc_cnt
      ans = max(ans, dp(i));
    printf("%d\n", ans);
  }
  return 0;
}
