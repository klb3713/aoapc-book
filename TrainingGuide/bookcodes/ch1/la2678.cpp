// LA2678 Subsequence O(n) version
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;
int A[maxn], B[maxn];
int main() {
  int n, S;
  while(scanf("%d%d", &n, &S) == 2 && n) {
    for(int i = 1; i <= n; i++) scanf("%d", &A[i]);
    B[0] = 0;
    for(int i = 1; i <= n; i++) B[i] = B[i-1] + A[i];
    int ans = n+1;
    int i = 1;
    for(int j = 1; j <= n; j++) {
      if(B[i-1] > B[j]-S) continue; // (1)没有满足条件的i，换下一个j
      while(B[i] <= B[j]-S) i++;    // (2)求满足B[i-1]<=B[j]-S的最大i
      ans = min(ans, j-i+1);
    }
    printf("%d\n", ans == n+1 ? 0 : ans);
  }
  return 0;
}
