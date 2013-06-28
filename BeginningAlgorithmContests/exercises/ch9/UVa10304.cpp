// UVa10304 Optimal Binary Search Tree
// Rujia Liu
// 题意：经典的OBST问题
// 算法：设d[i][j]为关键字i~j构造出的OBST的最小费用，sum(i,j)为i~j的权值之和
// d[i][j] = min{d[i][k-1] + d[k+1][j]} + sum(i,j) - f[k]，表示根结点为k，除了根之外其他结点的高度加1，因此费用要加上权值。
#include<cstdio>
#include<cstring>
const int maxn = 250 + 5;
int n, f[maxn], psum[maxn], d[maxn][maxn];

int dp(int i, int j) {
  if(i > j) return 0;
  int& ans = d[i][j];
  if(ans > 0) return ans;
  ans = -1;
  for(int k = i; k <= j; k++) {
    int v = dp(i,k-1) + dp(k+1,j) + psum[j] - psum[i-1] - f[k];
    if(ans < 0 || v < ans) ans = v;
  }
  return ans;
}

int main() {
  while(scanf("%d", &n) == 1 && n) {
    memset(psum, 0, sizeof(psum));
    for(int i = 1; i <= n; i++) { scanf("%d", &f[i]); psum[i] = psum[i-1] + f[i]; }
    memset(d, 0, sizeof(d));
    printf("%d\n", dp(1, n));
  }
  return 0;
}
