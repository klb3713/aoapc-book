/*
  习题2-9. 分数化小数（decimal）
  刘汝佳

  注意代码中对第c+1位四舍五入的处理
*/

#include<stdio.h>
int main() {
  int a, b, c;
  scanf("%d%d%d", &a, &b, &c);

  printf("%d.", a / b);
  a %= b;
  while(c--) {
    a *= 10;
    int q = a / b;
    if(c == 0 && (a % b) * 10 / b >= 5) q++;
    printf("%d", q);
    a %= b;
  }
  return 0;
}
