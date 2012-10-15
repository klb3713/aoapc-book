// UVa11464 Even Party
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 20;
const int INF = 1000000000;
int n, A[maxn][maxn], B[maxn][maxn];

int check(int s) {
  memset(B, 0, sizeof(B));
  for(int c = 0; c < n; c++) {
    if(s & (1<<c)) B[0][c] = 1;
    else if(A[0][c] == 1) return INF; // 1不能变成0
  }
  for(int r = 1; r < n; r++)
    for(int c = 0; c < n; c++) {
      int sum = 0; // 元素B[r-1][c]的上、左、右3个元素之和
      if(r > 1) sum += B[r-2][c];
      if(c > 0) sum += B[r-1][c-1];
      if(c < n-1) sum += B[r-1][c+1];
      B[r][c] = sum % 2;
      if(A[r][c] == 1 && B[r][c] == 0) return INF; // 1不能变成0
    }
  int cnt = 0;
  for(int r = 0; r < n; r++)
    for(int c = 0; c < n; c++) if(A[r][c] != B[r][c]) cnt++;
  return cnt;
}

int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%d", &n);
    for(int r = 0; r < n; r++)
      for(int c = 0; c < n; c++) scanf("%d", &A[r][c]);

    int ans = INF;
    for(int s = 0; s < (1<<n); s++)
      ans = min(ans, check(s));
    if(ans == INF) ans = -1;
    printf("Case %d: %d\n", kase, ans);
  }
  return 0;
}
