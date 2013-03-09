// UVa11609 Teams
// Rujia Liu

#include<stdio.h>
const int MOD = 1000000007;
long long pow_mod(int n, int k, int m) {
  if(!k) return 1;
  long long p = pow_mod(n, k/2, m);
  p = p * p % m;
  if(k&1) p = p * n % m;
  return p;
}

int main() {
  int T, n, k, m, a;
  scanf("%d", &T);
  for(int i = 1; i <= T; i++) {
    scanf("%d", &n);
    long long ans = pow_mod(2,n-1,MOD) * n % MOD;
    printf("Case #%d: %d\n", i, (int)ans);
  }
  return 0;
}
