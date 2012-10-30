// UVa11383 Golden Tiger Claw （更适合作为模板的版本）
// Rujia Liu
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 500 + 5; // 顶点的最大数目
const int INF = 1000000000;

struct KM {
  int n;                  // 左右顶点个数
  vector<int> G[maxn];    // 邻接表
  int W[maxn][maxn];      // 权值
  int Lx[maxn], Ly[maxn]; // 顶标
  int left[maxn];         // left[i]为右边第i个点的匹配点编号，-1表示不存在
  bool S[maxn], T[maxn];  // S[i]和T[i]为左/右第i个点是否已标记

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    memset(W, 0, sizeof(W));
  }

  void AddEdge(int u, int v, int w) {
    G[u].push_back(v);
    W[u][v] = w;
  }

  bool match(int u){
    S[u] = true;
    for(int i = 0; i < G[u].size(); i++) {
      int v = G[u][i];
      if (Lx[u]+Ly[v] == W[u][v] && !T[v]){
        T[v] = true;
        if (left[v] == -1 || match(left[v])){
          left[v] = u;
          return true;
        }
      }
    }
    return false;
  }

  void update(){
    int a = INF;
    for(int u = 0; u < n; u++) if(S[u])
      for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(!T[v]) a = min(a, Lx[u]+Ly[v] - W[u][v]);
      }
    for(int i = 0; i < n; i++) {
      if(S[i]) Lx[i] -= a;
      if(T[i]) Ly[i] += a;
    }
  }

  void solve() {    
    for(int i = 0; i < n; i++) {
      Lx[i] = *max_element(W[i], W[i]+n);
      left[i] = -1;
      Ly[i] = 0;
    }
    for(int u = 0; u < n; u++) {
      for(;;) {
        for(int i = 0; i < n; i++) S[i] = T[i] = false;
        if(match(u)) break; else update();
      }
    }
  }
};

KM solver;

int main(){
  int n, w;
  while(scanf("%d", &n) == 1) {
    solver.init(n);
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++) {
        scanf("%d", &w);
        solver.AddEdge(i, j, w);
      }
    solver.solve();
    int sum = 0;
    for(int i = 0; i < n-1; i++) { printf("%d ", solver.Lx[i]); sum += solver.Lx[i]; } printf("%d\n", solver.Lx[n-1]);
    for(int i = 0; i < n-1; i++) { printf("%d ", solver.Ly[i]); sum += solver.Ly[i]; } printf("%d\n", solver.Ly[n-1]);
    printf("%d\n", sum + solver.Lx[n-1] + solver.Ly[n-1]);
  }
  return 0;
}
