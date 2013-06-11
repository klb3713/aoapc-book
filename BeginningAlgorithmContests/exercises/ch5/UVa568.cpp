// UVa568 Just the Facts
// Rujia Liu
// 题意：输入整数0<=n<=10000，输出n!最右的非零数字
// 算法：预处理时用递推计算出所有结果。因为范围n<=10000比较小，保留结果的最后5位数字即可。

#include<cstdio>
const int maxn = 10001;
int ans[maxn];

int main() {
  ans[0] = 1;
  for(int i = 1; i < maxn; i++) {
    ans[i] = ans[i-1] * i;
    while(ans[i] % 10 == 0) ans[i] /= 10;
    ans[i] %= 100000; // 不能只保留个位数（想一想，为什么）
  }
  int n;
  while(scanf("%d", &n) == 1)
    printf("%5d -> %d\n", n, ans[n] % 10);
  return 0;
}
