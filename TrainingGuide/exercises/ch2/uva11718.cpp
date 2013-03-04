// UVa11718 Fantasy of a Summation
// Rujia Liu

#include<stdio.h>

int pow_mod(int n, int k, int m) {
  if(!k) return 1;
  int p = pow_mod(n, k/2, m);
  p = p * p % m;
  if(k&1) p = p * n % m;
  return p;
}

int main() {
  int T, n, k, m, a;
  scanf("%d", &T);
  for(int i = 1; i <= T; i++) {
    scanf("%d%d%d", &n, &k, &m);
    long long s = 0;
    for(int j = 0; j < n; j++) { scanf("%d", &a); s = (s+a)%m; }
    s = s * pow_mod(n,k-1,m) % m;
    s = s * (k % m) % m;
    printf("Case %d: %d\n", i, s);
  }
  return 0;
}
