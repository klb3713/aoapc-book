// LA4287 Proving Equivalences：使用Tarjan算法计算SCC
// Rujia Liu
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<stack>
using namespace std;

const int maxn = 20000 + 10;

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

int in0[maxn], out0[maxn];

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

    find_scc(n);

    for(int i = 1; i <= scc_cnt; i++) in0[i] = out0[i] = 1;
    for(int u = 0; u < n; u++)
      for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(sccno[u] != sccno[v]) in0[sccno[v]] = out0[sccno[u]] = 0;
      }
    int a = 0, b = 0;
    for(int i = 1; i <= scc_cnt; i++) {
      if(in0[i]) a++;
      if(out0[i]) b++;
    }
    int ans = max(a, b);
    if(scc_cnt == 1) ans = 0;
    printf("%d\n", ans);
  }
  return 0;
}
