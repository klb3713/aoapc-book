// UVa113 Power of Cryptography
// Rujia Liu
// 输入n和p，求p的n次方根。输出保证为1~10^9的整数
// 算法：题目给出的范围在double之内，直接用库函数求即可
#include<cstdio>
#include<cmath>

int main() {
  double n, p;
  while(scanf("%lf%lf", &n, &p) == 2)
    printf("%.0lf\n", pow(p, 1 / n));
  return 0;
}
