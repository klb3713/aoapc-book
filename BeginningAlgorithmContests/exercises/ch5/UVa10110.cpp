// UVa10110 Light, more light
// Rujia Liu
// 题意：经典的开灯问题，即判断n是否为完全平方数

#include<cstdio>
#include<cmath>

int main() {
  long long n;
  while(scanf("%lld", &n) == 1 && n) {
    long long s = floor(sqrt(n) + 0.5);
    if(s*s == n) printf("yes\n"); else printf("no\n"); // 注意如果s是int类型，s*s可能会溢出
  }
  return 0;
}
