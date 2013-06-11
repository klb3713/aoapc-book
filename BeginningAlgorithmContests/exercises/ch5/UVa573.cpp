// UVa573 The Snail
// Rujia Liu
// 题意：输入H, U, D, F，有一堵高度为H的墙，蜗牛第一天爬U米，后面每天少爬前一天U*F%，每天固定下滑D米，问第几天爬上来（高度>H）或者失败（高度<0）。
// 算法：模拟

#include<cstdio>
int main() {
  double H, U, D, F;
  while(scanf("%lf%lf%lf%lf", &H, &U, &D, &F) == 4 && H) {
    double p = 0, loss = U*F/100;
    for(int day = 1; ; day++) {
      if(U > 0) p += U;
      U -= loss;
      if(p > H) { printf("success on day %d\n", day); break; }
      p -= D;
      if(p < 0) { printf("failure on day %d\n", day); break; }
    }
  }
  return 0;
}
