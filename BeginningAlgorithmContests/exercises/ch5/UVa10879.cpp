// UVa10879 Code Refactoring
// Rujia Liu
// 题意：输入正整数n，找出四个不同的正整数a, b, c, d使得n=a*b=c*d
// 算法：直接枚举因子
#include<cstdio>
int main() {
  int T, n, kase = 0;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    int a = 0, c = 0;
    for(int i = 2; i <= n; i++)
      if(n % i == 0) {
        if(!a) a = i; else c = i;
        if(c) break;
      }
    printf("Case #%d: %d = %d * %d = %d * %d\n", ++kase, n, a, n/a, c, n/c);
  }
  return 0;
}
