// LA3126 Taxi Cab Scheme
// Rujia Liu
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 500 + 5; // 单侧顶点的最大数目

// 二分图最大基数匹配，邻接矩阵写法
struct BPM {
  int n, m;               // 左右顶点个数
  int G[maxn][maxn];      // 邻接表
  int left[maxn];         // left[i]为右边第i个点的匹配点编号，-1表示不存在
  bool T[maxn];           // T[i]为右边第i个点是否已标记

  void init(int n, int m) {
    this->n = n;
    this->m = m;
    memset(G, 0, sizeof(G));
  }

  bool match(int u){
    for(int v = 0; v < m; v++) if(G[u][v] && !T[v]) {
      T[v] = true;
      if (left[v] == -1 || match(left[v])){
        left[v] = u;
        return true;
      }
    }
    return false;
  }

  // 求最大匹配
  int solve() {
    memset(left, -1, sizeof(left));
    int ans = 0;
    for(int u = 0; u < n; u++) { // 从左边结点u开始增广
      memset(T, 0, sizeof(T));
      if(match(u)) ans++;
    }
    return ans;
  }

};

BPM solver;

int x1[maxn], y1[maxn], x2[maxn], y2[maxn], t1[maxn], t2[maxn];

inline int dist(int a, int b, int c, int d) {
  return abs(a-c) + abs(b-d);
}

int main(){
  int T;
  scanf("%d", &T);
  while(T--) {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
      int h, m;
      scanf("%d:%d%d%d%d%d", &h, &m, &x1[i], &y1[i], &x2[i], &y2[i]);
      t1[i] = h*60+m;
      t2[i] = t1[i] + dist(x1[i], y1[i], x2[i], y2[i]);
    }
    solver.init(n, n);
    for(int i = 0; i < n; i++)
      for(int j = i+1; j < n; j++)
        if(t2[i] + dist(x2[i], y2[i], x1[j], y1[j]) < t1[j]) solver.G[i][j] = 1; // 至少要提前1分钟到达
    printf("%d\n", n - solver.solve());
  }
  return 0;
}
