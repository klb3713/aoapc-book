// UVa11637 Garbage Remembering Exam
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 100010;
long double lf[maxn];
int n, k;

int main() {
  lf[0] = 0;
  lf[1] = 0;
  for(int i = 2; i <= 100000; i++)
    lf[i] = lf[i-1] + log((long double)i);
  int kase = 0;
  while(scanf("%d%d", &n, &k) == 2 && n) {
    long double sum = 0.0;
    printf("Case %d: ", ++kase);
    if(n == 1) { printf("0.0000\n"); continue; }
    if(n - 2*k - 1 <= 0) { printf("%d.0000\n", n); continue; }
    for(int i = 1; i <= n; i++) {
      int x = max(i-1-k, 0) + max(n-i-k, 0);
      if(x >= 2*k) {
        sum += exp(lf[x] - lf[x-2*k] + lf[n-2*k-1] - lf[n-1]);
      }
    }
    printf("%.4lf\n", (double)(n - sum));
  }
  return 0;
}
