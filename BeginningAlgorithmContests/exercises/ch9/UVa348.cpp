// UVa348 Optimal Array Multiplication Sequence
// Rujia Liu
// 题意：最优矩阵链乘，n<=10，要求输出方案
// 算法：动态规划。d[i][j]为矩阵i~j的最少乘法次数，则d[i][j] = min{d[i][k] + d[k+1][j] + a[i]*b[k]*b[j]}
// 输出方案的时候，记录d[i][j]的最优k，即sol[i][j]，然后递归打印
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 10 + 5;
int n, a[maxn], b[maxn], vis[maxn][maxn], d[maxn][maxn], sol[maxn][maxn];

int dp(int i, int j) {
  if(i >= j) return 0;
  if(vis[i][j]) return d[i][j];
  vis[i][j] = 1;
  int& ans = d[i][j];
  ans = -1;
  for(int k = i; k < j; k++) {
    int v = dp(i, k) + dp(k+1, j) + a[i] * b[k] * b[j];
    if(ans < 0 || v < ans) { ans = v; sol[i][j] = k; }
  }
  return ans;
}

void print(int i, int j) {
  if(i == j) printf("A%d", i+1);
  else {
    printf("(");
    int k = sol[i][j];
    print(i, k);
    printf(" x ");
    print(k+1, j);
    printf(")");
  }
}

int main() {
  int kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    for(int i = 0; i < n; i++) scanf("%d%d", &a[i], &b[i]);
    memset(vis, 0, sizeof(vis));
    dp(0, n-1);
    printf("Case %d: ", ++kase);
    print(0, n-1);
    printf("\n");
  }
  return 0;
}
