// UVa11865 Stream My Contest
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
const int maxn = 100 + 10;

// 固定根的最小树型图，邻接矩阵写法
struct MDST {
  int n;
  int w[maxn][maxn]; // 边权
  int vis[maxn];     // 访问标记，仅用来判断无解
  int ans;           // 计算答案
  int removed[maxn]; // 每个点是否被删除
  int cid[maxn];     // 所在圈编号
  int pre[maxn];     // 最小入边的起点
  int iw[maxn];      // 最小入边的权值
  int max_cid;       // 最大圈编号

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++) w[i][j] = INF;
  }

  void AddEdge(int u, int v, int cost) {
    w[u][v] = min(w[u][v], cost); // 重边取权最小的
  }

  // 从s出发能到达多少个结点
  int dfs(int s) {
    vis[s] = 1;
    int ans = 1;
    for(int i = 0; i < n; i++)
      if(!vis[i] && w[s][i] < INF) ans += dfs(i);
    return ans;
  }

  // 从u出发沿着pre指针找圈
  bool cycle(int u) {
    max_cid++;
    int v = u;
    while(cid[v] != max_cid) { cid[v] = max_cid; v = pre[v]; }
    return v == u;
  }

  // 计算u的最小入弧，入弧起点不得在圈c中
  void update(int u) {
    iw[u] = INF;
    for(int i = 0; i < n; i++)
      if(!removed[i] && w[i][u] < iw[u]) {
        iw[u] = w[i][u];
        pre[u] = i;
      }
  }

  // 根结点为s，如果失败则返回false
  bool solve(int s) {    
    memset(vis, 0, sizeof(vis));
    if(dfs(s) != n) return false;

    memset(removed, 0, sizeof(removed));
    memset(cid, 0, sizeof(cid));
    for(int u = 0; u < n; u++) update(u);
    pre[s] = s; iw[s] = 0; // 根结点特殊处理
    ans = max_cid = 0;
    for(;;) {
      bool have_cycle = false;
      for(int u = 0; u < n; u++) if(u != s && !removed[u] && cycle(u)){
        have_cycle = true;
        // 以下代码缩圈，圈上除了u之外的结点均删除
        int v = u;
        do {
          if(v != u) removed[v] = 1;
          ans += iw[v];
          // 对于圈外点i，把边i->v改成i->u（并调整权值）；v->i改为u->i
          // 注意圈上可能还有一个v'使得i->v'或者v'->i存在，因此只保留权值最小的i->u和u->i
          for(int i = 0; i < n; i++) if(cid[i] != cid[u] && !removed[i]) {
            if(w[i][v] < INF) w[i][u] = min(w[i][u], w[i][v]-iw[v]);
            w[u][i] = min(w[u][i], w[v][i]);
            if(pre[i] == v) pre[i] = u;
          }
          v = pre[v];
        } while(v != u);        
        update(u);
        break;
      }
      if(!have_cycle) break;
    }
    for(int i = 0; i < n; i++)
      if(!removed[i]) ans += iw[i];
    return true;
  }
};

//////// 题目相关
MDST solver;

struct Edge {
  int u, v, b, c;
  bool operator < (const Edge& rhs) const {
    return b > rhs.b;
  }
};

const int maxm = 10000 + 10;
int n, m, C;
Edge edges[maxm];

// 取b前cnt大的边构造网络，判断最小树型图的边权和是否小于C
bool check(int cnt) {
  solver.init(n);
  for(int i = 0; i < cnt; i++)
    solver.AddEdge(edges[i].u, edges[i].v, edges[i].c);
  if(!solver.solve(0)) return false;
  return solver.ans <= C;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d%d", &n, &m, &C);
    for(int i = 0; i < m; i++) {
      scanf("%d%d%d%d", &edges[i].u, &edges[i].v, &edges[i].b, &edges[i].c);      
    }
    sort(edges, edges+m);
    int L = 1, R = m, ans = -1;
    while(L <= R) {
      int M = L + (R-L)/2;
      if(check(M)) { ans = edges[M-1].b; R = M-1; }
      else L = M+1;
    }
    if(ans < 0) printf("streaming not possible.\n");
    else printf("%d kbps\n", ans);
  }
  return 0;
}
