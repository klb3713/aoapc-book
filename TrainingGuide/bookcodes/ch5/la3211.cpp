// LA3211 Now or Later
// Rujia Liu
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;

const int maxn = 2000 + 10;

struct TwoSAT {
  int n;
  vector<int> G[maxn*2];
  bool mark[maxn*2];
  int S[maxn*2], c;

  bool dfs(int x) {
    if (mark[x^1]) return false;
    if (mark[x]) return true;
    mark[x] = true;
    S[c++] = x;
    for (int i = 0; i < G[x].size(); i++)
      if (!dfs(G[x][i])) return false;
    return true;
  }

  void init(int n) {
    this->n = n;
    for (int i = 0; i < n*2; i++) G[i].clear();
    memset(mark, 0, sizeof(mark));
  }

  // x = xval or y = yval
  void add_clause(int x, int xval, int y, int yval) {
    x = x * 2 + xval;
    y = y * 2 + yval;
    G[x^1].push_back(y);
    G[y^1].push_back(x);
  }

  bool solve() {
    for(int i = 0; i < n*2; i += 2)
      if(!mark[i] && !mark[i+1]) {
        c = 0;
        if(!dfs(i)) {
          while(c > 0) mark[S[--c]] = false;
          if(!dfs(i+1)) return false;
        }
      }
    return true;
  }
};

///////// 题目相关
#include<algorithm>

TwoSAT solver;

int n, T[maxn][2];

bool test(int diff) {
  solver.init(n);
    for(int i = 0; i < n; i++) for(int a = 0; a < 2; a++)
      for(int j = i+1; j < n; j++) for(int b = 0; b < 2; b++)
        if(abs(T[i][a] - T[j][b]) < diff) solver.add_clause(i, a^1, j, b^1);
  return solver.solve();
}

int main() {
  while(scanf("%d", &n) == 1 && n) {
    int L = 0, R = 0;
    for(int i = 0; i < n; i++) for(int a = 0; a < 2; a++) {
      scanf("%d", &T[i][a]);
      R = max(R, T[i][a]);
    }
    while(L < R) {
      int M = L + (R-L+1)/2;
      if(test(M)) L = M; else R = M-1;
    }
    printf("%d\n", L);
  }
  return 0;
}
