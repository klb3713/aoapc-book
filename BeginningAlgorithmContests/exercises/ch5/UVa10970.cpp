// UVa10970 Big Chocolate
// Rujia Liu
// 题意：m*n的巧克力，至少切几刀能切成m*n个1*1的巧克力？每次只能把一块切成两块
// 算法：切一刀多一块，一共多了m*n-1块，所以...

#include<cstdio>
int main() {
  int m, n;
  while(scanf("%d%d", &m, &n) == 2) printf("%d\n", m*n-1);
  return 0;
}
