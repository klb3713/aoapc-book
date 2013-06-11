// UVa10161 Ant on a Chessboard
// Rujia Liu
/* 题意：按照如下规律填表，输入n，输出坐标。比如8在(2,3)

25 24 23 22 21
10 11 12 13 20
 9  8  7 14 19
 2  3  6 15 18
 1  4  5 16 17

 算法：数是一圈一圈填进去的，先算出是哪一圈，然后根据奇偶性推断。
 比如8是第3圈，走的顺序是从右下到左上。这一圈一共有5个元素，其中8是第4步，第3步开始转折。
*/

#include<cstdio>
#include<cmath>
int main() {
  int n;
  while(scanf("%d", &n) == 1 && n) {
    int s = floor(sqrt(n)) + 1; // 求最小s使得n<=s^2，则n在第s圈
    while(n <= (s-1)*(s-1)) s--;
    int len = s*s - (s-1)*(s-1); // 这一圈的元素个数
    int step = n - (s-1)*(s-1);  // 这一圈走的步数
    if(s % 2 == 0) { // 从左上到右下
      if(step <= len/2) printf("%d %d\n", step, s); // 没走到转折点
      else printf("%d %d\n", s, len-step+1);
    } else { // 从右下到左上
      if(step <= len/2) printf("%d %d\n", s, step); // 没走到转折点
      else printf("%d %d\n", len-step+1, s);
    }
  }
  return 0;
}
