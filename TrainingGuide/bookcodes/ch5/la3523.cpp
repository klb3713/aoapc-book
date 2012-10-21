// LA3523 Knights of the Round Table
// Rujia Liu
#include<cstdio>
#include<stack>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

struct Edge { int u, v; };

const int maxn = 1000 + 10;
int pre[maxn], iscut[maxn], bccno[maxn], dfs_clock, bcc_cnt; // 割顶的bccno无意义
vector<int> G[maxn], bcc[maxn];

stack<Edge> S;

int dfs(int u, int fa) {
  int lowu = pre[u] = ++dfs_clock;
  int child = 0;
  for(int i = 0; i < G[u].size(); i++) {
    int v = G[u][i];
    Edge e = (Edge){u, v};
    if(!pre[v]) { // 没有访问过v
      S.push(e);
      child++;
      int lowv = dfs(v, u);
      lowu = min(lowu, lowv); // 用后代的low函数更新自己
      if(lowv >= pre[u]) {
        iscut[u] = true;
        bcc_cnt++; bcc[bcc_cnt].clear();
        for(;;) {
          Edge x = S.top(); S.pop();
          if(bccno[x.u] != bcc_cnt) { bcc[bcc_cnt].push_back(x.u); bccno[x.u] = bcc_cnt; }
          if(bccno[x.v] != bcc_cnt) { bcc[bcc_cnt].push_back(x.v); bccno[x.v] = bcc_cnt; }
          if(x.u == u && x.v == v) break;
        }
      }
    }
    else if(pre[v] < pre[u] && v != fa) {
      S.push(e);
      lowu = min(lowu, pre[v]); // 用反向边更新自己
    }
  }
  if(fa < 0 && child == 1) iscut[u] = 0;
  return lowu;
}

void find_bcc(int n) {
  // 调用结束后S保证为空，所以不用清空
  memset(pre, 0, sizeof(pre));
  memset(iscut, 0, sizeof(iscut));
  memset(bccno, 0, sizeof(bccno));
  dfs_clock = bcc_cnt = 0;
  for(int i = 0; i < n; i++)
    if(!pre[i]) dfs(i, -1); 
}

int odd[maxn], color[maxn];
bool bipartite(int u, int b) {
  for(int i = 0; i < G[u].size(); i++) {
    int v = G[u][i]; if(bccno[v] != b) continue;
    if(color[v] == color[u]) return false;
    if(!color[v]) {
      color[v] = 3 - color[u];
      if(!bipartite(v, b)) return false;
    }
  }
  return true;
}

int A[maxn][maxn];

int main() {
  int kase = 0, n, m;
  while(scanf("%d%d", &n, &m) == 2 && n) {
    for(int i = 0; i < n; i++) G[i].clear();

    memset(A, 0, sizeof(A));
    for(int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v); u--; v--; A[u][v] = A[v][u] = 1;
    }
    for(int u = 0; u < n; u++)
      for(int v = u+1; v < n; v++)
        if(!A[u][v]) { G[u].push_back(v); G[v].push_back(u); }

    find_bcc(n);

    memset(odd, 0, sizeof(odd));
    for(int i = 1; i <= bcc_cnt; i++) {
      memset(color, 0, sizeof(color));
      for(int j = 0; j < bcc[i].size(); j++) bccno[bcc[i][j]] = i; // 主要是处理割顶
      int u = bcc[i][0];
      color[u] = 1;
      if(!bipartite(u, i))
        for(int j = 0; j < bcc[i].size(); j++) odd[bcc[i][j]] = 1;
    }
    int ans = n;
    for(int i = 0; i < n; i++) if(odd[i]) ans--;
    printf("%d\n", ans);
  }
  return 0;
}
