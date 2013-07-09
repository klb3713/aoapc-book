// UVa11029 Leading and Trailing
// Rujia Liu
// 题意：输入正整数n, k, 输出n^k的前三位和后三位。n是32位正整数，k<=10^7
// 算法：最后三位用快速幂取模即可；前三位可以近似计算。设n^k=a*10^b（1<=a<10），则klog10(n) = b+log10(a)
// 取log10(a)为klog10(n)的小数部分即可。因此前三位就是a*100的整数部分。
#include<cstdio>
#include<cmath>
int pow_mod(int a, long long p, int mod) {
  if(p == 0) return 1;
  int ans = pow_mod(a, p/2, mod);
  ans = (long long)ans * ans % mod;
  if(p%2) ans = (long long)ans * a % mod;
  return ans;
}

int main() {
  int T, n, k;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &n, &k);
    int last = pow_mod(n, k, 1000);
    int first = (int)pow(10, fmod(k * log10(n), 1) + 2); // 直接取整而不是四舍五入
    printf("%d...%03d\n", first, last);
  }
  return 0;
}
