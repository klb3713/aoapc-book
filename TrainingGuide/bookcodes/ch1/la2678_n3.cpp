// LA2678 Subsequence O(n^3) version
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int A[maxn];
int main() {
  int n, S;
  while(scanf("%d%d", &n, &S) == 2 && n) {
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    int ans = n+1;
    for(int i = 1; i <= n; i++)
      for(int j = i; j <= n; j++) {
        int sum = 0;
        for(int k = i; k <= j; k++) sum += A[k];
        if(sum >= S) ans = min(ans, j-i+1);
      }
    printf("%d\n", ans == n+1 ? 0 : ans);
  }
  return 0;
}
