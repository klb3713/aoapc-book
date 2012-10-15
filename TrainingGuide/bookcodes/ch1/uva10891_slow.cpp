// UVa10891 Sum (slower version)
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int S[110], A[110], d[110][110], vis[110][110], n;

int dp(int i, int j) {
  if(vis[i][j]) return d[i][j];
  vis[i][j] = 1;
  int m = 0; // 全部取光
  for(int k = i+1; k <= j; k++) m = min(m, dp(k,j));
  for(int k = i; k < j; k++) m = min(m, dp(i,k));
  d[i][j] = S[j]-S[i-1] - m; // 如果i从0开始编号，这里得判断一下是否i==0
  return d[i][j];
}

int main() {
  while(scanf("%d", &n) && n) {
    S[0] = 0;
    for(int i = 1; i <= n; i++) { scanf("%d", &A[i]); S[i]=S[i-1]+A[i]; }
    memset(vis, 0, sizeof(vis)); // 千万不要漏掉
    printf("%d\n", 2*dp(1,n)-S[n]);
  }
  return 0;
}
