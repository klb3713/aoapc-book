// LA3700 Interesting Yang Hui Triangle
// Rujia Liu
#include<cstdio>
int main() {
  int kase = 0, n, p;
  while(scanf("%d%d", &p, &n) == 2 && p) {
    int ans = 1;
    while(n > 0) {
      ans = ans * (n%p+1) % 10000;
      n /= p;
    }
    printf("Case %d: %04d\n", ++kase, ans);
  }
  return 0;
}
