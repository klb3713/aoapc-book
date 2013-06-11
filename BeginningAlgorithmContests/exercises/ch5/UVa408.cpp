// UVa408 Uniform Generator
// Rujia Liu
// 题意：
// 一种伪随机数生成方法是利用递推式 seed(x+1) = [seed(x) + STEP)%MOD。
// 输入STEP和MOD，判断随机数出现循环之前是否可以遍历0~MOD-1的所有数
// 比如STEP = 3, MOD = 5，生成的随机数为0, 3, 1, 4, 2, 0, 3, 1, 4, 2, ... 符合要求
// 再比如STEP = 15, MOD = 20，生成的随机数为0, 15, 10, 5, ... 不符合要求
// 算法：分析可知当且仅当STEP, MOD互素的时候符合要求

#include<cstdio>

int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a%b);
}

int main() {
  int a, b;
  while(scanf("%d%d", &a, &b) == 2) {
    printf("%10d%10d    ", a, b);
    if(gcd(a, b) == 1) printf("Good"); else printf("Bad");
    printf(" Choice\n\n");
  }
  return 0;
}
