// LA5135 Mining Your Own Business
// Rujia Liu
#include<cstdio>
#include<stack>
#include<vector>
#include<map>
#include<algorithm>
#include<cstring>

using namespace std;

typedef long long LL;

struct Edge { int u, v; };

const int maxn = 100000 + 10;
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

struct ID {
  map<int, int> m;
  int cnt;
  ID():cnt(0) { }
  int get(int x) {
    if(!m.count(x)) m[x] = cnt++;
    return m[x];
  }
};

int main() {
  int kase = 0, n;
  while(scanf("%d", &n) == 1 && n) {
    memset(pre, 0, sizeof(pre));
    memset(iscut, 0, sizeof(iscut));
    memset(bccno, 0, sizeof(bccno));
    for(int i = 0; i < n*2; i++) G[i].clear();
    dfs_clock = bcc_cnt = 0;

    ID id;
    for(int i = 0; i < n; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u = id.get(u); v = id.get(v);
      G[u].push_back(v); G[v].push_back(u);
    }
    dfs(0, -1); // 调用结束后S保证为空，所以不用清空

    LL ans1 = 0, ans2 = 1;
    for(int i = 1; i <= bcc_cnt; i++) {
      int cut_cnt = 0;
      for(int j = 0; j < bcc[i].size(); j++)
        if(iscut[bcc[i][j]]) cut_cnt++;
      if(cut_cnt == 1) {
        ans1++; ans2 *= (LL)(bcc[i].size() - cut_cnt);
      }
    }
    if(bcc_cnt == 1) {
      ans1 = 2; ans2 = bcc[1].size() * (bcc[1].size() - 1) / 2;
    }
    printf("Case %d: %lld %lld\n", ++kase, ans1, ans2);
  }
  return 0;
}
