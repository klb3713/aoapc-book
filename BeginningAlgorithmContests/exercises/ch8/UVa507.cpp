// UVa507 Jill Rides Again
// Rujia Liu
// 题意：数轴上有n个点1~n，已知相邻两个点之间的权值，找两个点(i,j)，使得之间的权值之和尽量的大。如果有多解，让j-i尽量大。如果还有多解，让i尽量小。
// 算法：标准算法。
#include<cstdio>
int besti, bestj, ans;

void check(int i, int j, int v) {
  if(v > ans || (v == ans && (j-i > bestj-besti || (j-i == bestj-besti && i < besti)))) {
    ans = v;
    besti = i;
    bestj = j;
  }
}

const int maxn = 20000 + 5;
int n, a[maxn];

void solve() {
  if(--n == 0) { ans = -1; return; }
  for(int i = 0; i < n; i++) scanf("%d", &a[i]);
  int v = a[0];
  ans = v;
  besti = bestj = 0;
  int lasti = 0;
  for(int i = 1; i < n; i++) {
    if(v < 0) { v = 0; lasti = i; }
    v += a[i];
    check(lasti, i, v);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%d", &n);
    solve();
    if(ans < 0) printf("Route %d has no nice parts\n", kase);
    else printf("The nicest part of route %d is between stops %d and %d\n", kase, besti+1, bestj+2);
  }
  return 0;
}
