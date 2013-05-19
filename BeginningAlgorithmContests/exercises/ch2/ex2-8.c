/*
  习题2-8. 子序列的和（subsequence）
  刘汝佳

  本题的陷阱是：如果写成sum += 1.0/(i*i)的话，会在计算i*i的时候溢出
*/

#include<stdio.h>
int main() {
  int i, n, m;
  scanf("%d%d", &n, &m);  
  
  double sum = 0;
  for(i = n; i <= m; i++) {
    sum += 1.0 / i / i;
  }
  printf("%.5lf\n", sum);
  return 0;
}
