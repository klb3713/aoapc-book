// UVa111 The Twin Towers
// Rujia Liu
// 题意：求两个序列的LCS长度
// 算法：LCS
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;
int n, m, A[maxn], B[maxn], d[maxn][maxn];

int LCS(int* A, int n, int* B, int m) {
  memset(d, 0, sizeof(d));
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++) {
      if(A[i-1] == B[j-1]) d[i][j] = d[i-1][j-1] + 1;
      else d[i][j] = max(d[i][j-1], d[i-1][j]);
    }
  return d[n][m];
}

int main() {
  int kase = 0;
  while(cin >> n >> m) {
    if(n == 0 && m == 0) break;
    for(int i = 0; i < n; i++) cin >> A[i];
    for(int i = 0; i < m; i++) cin >> B[i];
    cout << "Twin Towers #" << ++kase << "\n";
    cout << "Number of Tiles : " << LCS(A, n, B, m) << "\n\n";
  }
  return 0;
}
