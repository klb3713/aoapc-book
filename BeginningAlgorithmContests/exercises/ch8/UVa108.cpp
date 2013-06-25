// UVa108 Maximum Sum
// Rujia Liu
// 题意：输入一个n*n矩阵，找一个和最大的子矩阵
// 算法：首先计算每一列的前缀和，然后枚举第一行和最后一行，把问题转化为一维最大连续和问题
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;
int A[maxn][maxn], psum[maxn][maxn], B[maxn];

// a[0~n-1]的最大连续和问题
int maximum1D(int* a, int n) {
  int v = a[0];
  int ans = v;
  for(int i = 1; i < n; i++) {
    if(v < 0) v = 0;
    v += a[i];
    ans = max(ans, v);
  }
  return ans;
}

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
      scanf("%d", &A[i][j]);

  // 计算前缀和
  memset(psum, 0, sizeof(psum));
  for(int col = 1; col <= n; col++) {
    for(int row = 1; row <= n; row++)
      psum[col][row] = psum[col][row-1] + A[row][col];
  }

  int ans = -1000000000;
  for(int row1 = 1; row1 <= n; row1++)
    for(int row2 = row1; row2 <= n; row2++) {
      for(int col = 1; col <= n; col++)
        B[col-1] = psum[col][row2] - psum[col][row1-1];
      ans = max(ans, maximum1D(B, n));
    }
  printf("%d\n", ans);
  return 0;
}
