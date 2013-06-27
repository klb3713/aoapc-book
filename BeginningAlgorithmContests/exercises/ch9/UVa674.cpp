// UVa674 Coin Change
// Rujia Liu
// 题意：有50, 25, 10, 5, 1分硬币。输入n，问n分钱有多少种组成方法。n<=7489
// 算法：DP。d[i][j]表示前i（0<=i<5）种硬币组成j分钱有多少种方法。边界为d[0][*]=1。
// 注意输入只有一个整数，可以打表
#include<cstdio>
const int maxn = 7500;
const int n_coins = 5;
const int coins[] = {1, 5, 10, 25, 50};
int d[n_coins][maxn + 1];

void dp(int n) {
  for(int i = 0; i < n_coins; i++)
    for(int j = 0; j <= n; j++) {
      if(i == 0) d[i][j] = 1; // 用1分钱组成任意的j都只有一种方法
      else {
        d[i][j] = 0;
        for(int k = 0; k <= j; k += coins[i]) d[i][j] += d[i-1][j-k];
      }
    }
}

int main() {
  dp(maxn);
  int n;
  while(scanf("%d", &n) == 1) printf("%d\n", d[n_coins-1][n]);
  return 0;
}
