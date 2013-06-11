// UVa11044 Searching for Nessy
// Rujia Liu
// 题意：最少用多少个3x3棋盘覆盖nxm棋盘？边界格子不用覆盖
// 算法：实际只需要覆盖(n-2)*(m-2)，行需要((n-2)-1)/3+1个，化简为n/3，列需要m/3个，相乘即可

#include<cstdio>
int main() {
  int T, n, m;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &n, &m);
    printf("%d\n", (n/3)*(m/3));
  }
  return 0;
}
