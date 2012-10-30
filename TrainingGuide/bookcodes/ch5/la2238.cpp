// LA2238 Fixed Partition Memory Management
// Rujia Liu
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int maxn = 500 + 5; // 顶点的最大数目
const int INF = 1000000000;

// 最大权匹配
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

const int maxp = 50 + 5; // 程序(program)的最大数目
const int maxr = 10 + 5; // 区域(region)的最大数目
int n, m;                // 程序数目和区域数目
int runtime[maxp][maxr]; // runtime[p][r]为程序p在区域r中的运行时间

// 打印具体方案
void print_solution() {
  int start[maxp], region_number[maxp], total = 0; // 起始时刻、分配到得区域编号、总回转时间
  for(int region = 0; region < m; region++) {
    vector<int> programs; // 本region执行的所有程序，按照逆序排列（因为是指“倒数”第pos个程序）
    for(int pos = 0; pos < n; pos++) {
      int right = region * n + pos;
      int left = solver.left[right];
      if(left >= n) break; // 匹配到虚拟结点，说明本region已经没有更多程序了
      programs.push_back(left);
      region_number[left] = region;
      total -= solver.W[left][right]; // 权值取过相反数
    }
    reverse(programs.begin(), programs.end());
    int time = 0;
    for(int i = 0; i < programs.size(); i++) {
      start[programs[i]] = time;
      time += runtime[programs[i]][region];
    }
  }

  printf("Average turnaround time = %.2lf\n", (double)total / n);
  for(int p = 0; p < n; p++)
    printf("Program %d runs in region %d from %d to %d\n", p+1, region_number[p]+1, start[p], start[p]+runtime[p][region_number[p]]);
  printf("\n");
}

int main(){
  int kase = 0;
  while(scanf("%d%d", &m, &n) == 2 && m && n) {
    solver.init(m*n);
    int size[maxr];
    for(int region = 0; region < m; region++) scanf("%d", &size[region]);
    for(int program = 0; program < n; program++) {
      int s[10], t[10], k;
      scanf("%d", &k);
      for(int i = 0; i < k; i++) scanf("%d%d", &s[i], &t[i]);

      for(int region = 0; region < m; region++) {
        // 计算程序p在内存区域r中的运行时间
        int& time = runtime[program][region];
        time = INF;
        if(size[region] < s[0]) continue;
        for(int i = 0; i < k; i++)
          if(i == k-1 || size[region] < s[i+1]) {
            time = t[i];
            break;
          }

        // 连边X(program) -> Y(region,pos)
        for(int pos = 0; pos < n; pos++)
          solver.AddEdge(program, region * n + pos, -(pos + 1) * time); // 本题要求最小值，权值要取相反数
      }
    }

    // 补完其他边
    for(int i = n; i < n*m; i++)
      for(int j = 0; j < n*m; j++)
        solver.AddEdge(i, j, 1);

    solver.solve();

    printf("Case %d\n", ++kase);
    print_solution();
  }
  return 0;
}
