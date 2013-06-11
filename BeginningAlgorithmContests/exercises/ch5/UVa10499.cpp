// UVa10499 The Land of Justice
// Rujia Liu
// 题意：把球均分成n分，表面积增加了百分之多少？
// 算法：球的表面积为4*pi*r^2，切割之后每一块的总侧面积为pi*r^2。把pi*r^2提出来，相当于原来是4，增加了n，除非n=1
#include<cstdio>
int main() {
  int n;
  while(scanf("%d", &n) == 1 && n >= 0) {
    printf("%lld%%\n", n == 1 ? 0 : 25LL*n);
  }
  return 0;
}
