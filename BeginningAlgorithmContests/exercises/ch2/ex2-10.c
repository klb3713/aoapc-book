/*
  习题2-10. 排列（permutation）
  刘汝佳

  由于第二章还没有介绍数组和字符串，这里采用了一种略显复杂的方法来判断是否每个数字都出现
*/

#include<stdio.h>
int main() {
  int abc;
  for(abc = 123; abc <= 329; abc++) {
    int def = abc*2;
    int ghi = abc*3;
    int big = abc * 1000000 + def * 1000 + ghi;
    int ok = 1, d;
    for(d = 1; d <= 9; d++) {
      int n = big;
      int seen = 0;
      while(n > 0) {
        if(n % 10 == d) seen = 1;
        n /= 10;
      }
      if(!seen) {
        ok = 0; /* 数字d没有出现 */
        break;
      }
    }
    if(ok) printf("%d %d %d\n", abc, def, ghi);
  }
  return 0;
}
