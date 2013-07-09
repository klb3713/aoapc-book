// UVa10219 Find the ways !
// Rujia Liu
// 题意：求C(n,k)在十进制下是几位数
// 算法：求log(10, C(n,k))即可
#include<cstdio>
#include<cmath>
double lgC(int n, int m) {
  double ans = 1;
  if(n-m > m) m = n-m;
  for(int i = m+1; i <= n; i++) ans += log10(i);
  for(int i = 1; i <= n-m; i++) ans -= log10(i);
  return ans;
}

int main() {
  int n, k;
  while(scanf("%d%d", &n, &k) == 2)
    printf("%.0lf\n", floor(lgC(n, k)));
  return 0;
}
