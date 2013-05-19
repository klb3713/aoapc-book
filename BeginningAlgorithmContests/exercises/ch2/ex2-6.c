/*
  习题2-6. 调和级数（harmony）
  刘汝佳
*/

#include<stdio.h>
int main() {
  int i, n;
  double sum = 0;
  scanf("%d", &n);
  for(i = 1; i <= n; i++)
    sum += 1.0 / i;
  printf("%.3lf\n", sum);
  return 0;
}
