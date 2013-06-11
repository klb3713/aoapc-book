// UVa10916 Factstone Benchmark
// Rujia Liu
// 题意：假设计算机字长10年翻一翻，比如1960是4-bit, 1970是8-bit, ..., 2000是64-bit。输入年份，求最大的n使得最新计算机的字长可以装下n!
// 算法：枚举即可，用对数判断

#include<cstdio>
#include<cmath>

// 求最大的n使得n!<=2^(2^k)，即sum{log(i)} <= 2^k * log(2)
int solve(int k) {
  double M = pow(2, k), sum = 0;
  for(int i = 1; ; i++) {
    sum += log(i);
    if(sum > M * log(2)) return i-1;
  }
}

int main() {
  int y;
  while(scanf("%d", &y) == 1 && y) printf("%d\n", solve(y/10 - 194));
  return 0;
}
