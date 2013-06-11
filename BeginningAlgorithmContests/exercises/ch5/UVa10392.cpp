// UVa10392 Factoring Large Numbers
// Rujia Liu
// 题意：分解素因子。输入64位带符号整数，保证最多只有一个因子超过10^6
// 算法：直接枚举因子
#include<cstdio>
#include<cmath>
int main() {
  long long n;
  while(scanf("%lld", &n) == 1 && n >= 0) {
    long long limit = floor(sqrt(n) + 0.5);
    if(limit > 1000000) limit = 1000000;
    for(int i = 2; i <= limit; i++)
      while(n % i == 0) { printf("    %d\n", i); n /= i; }
    if(n > 1) printf("    %lld\n", n);
    printf("\n");
  }
  return 0;
}
