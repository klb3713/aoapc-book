// UVa10405 Longest Common Subsequence
// Rujia Liu
// 题意：输入两个字符串，求最长公共子序列长度
// 算法：LCS
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;

char A[maxn], B[maxn];
int d[maxn][maxn];

int LCS(const char* A, int n, const char* B, int m) {
  memset(d, 0, sizeof(d));
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++) {
      if(A[i-1] == B[j-1]) d[i][j] = d[i-1][j-1] + 1;
      else d[i][j] = max(d[i][j-1], d[i-1][j]);
    }
  return d[n][m];
}

int main() {
  while(fgets(A, maxn, stdin) != NULL) {
    fgets(B, maxn, stdin);
    printf("%d\n", LCS(A, strlen(A)-1, B, strlen(B)-1)); // 减1是因为fgets会读到回车
  }
  return 0;
}
