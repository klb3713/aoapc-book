// UVa10891 Sum (with optimizations)
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int S[110], A[110], d[110][110], vis[110][110], f[110][110], g[110][110], n;

// f[i+1][j] = min{d(i+1,j),d(i+2,j)...,d(j,j)}
// g[i][j-1] = min{d(i,j-1),d(i,j-2)...,d(i,i)}
int main() {
  while(scanf("%d", &n) && n) {
    S[0] = 0;
    for(int i = 1; i <= n; i++) { scanf("%d", &A[i]); S[i]=S[i-1]+A[i]; }
    for(int i = 1; i <= n; i++) f[i][i] = g[i][i] = d[i][i] = A[i]; // 边界
    for(int L = 1; L < n; L++) // 按照L=j-i递增的顺序计算
      for(int i = 1; i+L <= n; i++) {
        int j = i+L;
        int m = 0; // m = min{f(i+1,j), g(i,j-1), 0}
        m = min(m, f[i+1][j]);
        m = min(m, g[i][j-1]);
        d[i][j] = S[j]-S[i-1] - m;
        f[i][j] = min(d[i][j], f[i+1][j]); // 递推f和g
        g[i][j] = min(d[i][j], g[i][j-1]);
      }
    printf("%d\n", 2*d[1][n]-S[n]);
  }
  return 0;
}
