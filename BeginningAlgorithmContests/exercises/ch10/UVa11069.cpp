// UVa11069 A Graph Problem
// Rujia Liu
// 题意：给一条长度为n的链。求它有多少个极大独立集
// 算法：考虑选不选第一个点的情况，可以得到f(n)=f(n-2)+f(n-3)
#include<cstdio>
const int maxn = 76;
int f[maxn+1];

int main() {
  f[1] = 1, f[2] = 2, f[3] = 2;
  for(int i = 4; i <= maxn; i++) f[i] = f[i-2] + f[i-3];
  int n;
  while(scanf("%d", &n) == 1) printf("%d\n", f[n]);
  return 0;
}

