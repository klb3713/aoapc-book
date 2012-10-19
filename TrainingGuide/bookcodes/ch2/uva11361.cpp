// UVa11361 Investigating Div-Sum Property （限于篇幅，书上无此代码）
// Rujia Liu
#include<cstdio>
#include<cstring>
using namespace std;

int MOD; // 题目中叫k，改名为MOD可以让代码更清晰
int pow10[10];

// 整数n除以MOD的余数，返回0~MOD-1
int mod(int n) {
  return (n % MOD + MOD) % MOD;
}

// 共d个数字，数字之和除以k的余数为m1，整数本身除以k的余数为m2
int memo[11][90][90];
int f(int d, int m1, int m2) {
  if(d == 0) return m1 == 0 && m2 == 0 ? 1 : 0;

  int& ans = memo[d][m1][m2];
  if(ans >= 0) return ans;
  ans = 0;
  for(int x = 0; x <= 9; x++)
    ans += f(d-1, mod(m1-x), mod(m2-x*pow10[d-1]));
  return ans;
}

// 统计0~n-1中满足条件的整数个数（和书上的分析有一点出入，但没有本质区别）
int sumf(int n) {
  char digits[11];
  sprintf(digits, "%d", n);
  int nd = strlen(digits);

  int base = 0; // 当前区间的左边界
  int sumd = 0; // 当前区间的左边界的数字和
  int ans = 0;
  for(int i = 0; i < nd; i++) { // 有i个数字(i>=0)
    int na = nd - 1 - i; // 星号的个数
    for(int d = 0; d < digits[i] - '0'; d++) {
      int cnt = f(na, mod(-sumd - d), mod(-base - d*pow10[na]));
      ans += cnt;
    }
    base += (digits[i] - '0') * pow10[na];
    sumd += (digits[i] - '0');
  }
  return ans;
}

int main() {
  pow10[0] = 1;
  for(int i = 1; i <= 9; i++) pow10[i] = pow10[i-1] * 10;

  int T;
  scanf("%d", &T);
  while(T--) {
    int a, b;
    scanf("%d%d%d", &a, &b, &MOD);
    memset(memo, -1, sizeof(memo));
    if(MOD > 85) printf("0\n"); // 数字和最多为1+9*9=82，如果MOD大于此值，一定无解
    else printf("%d\n", sumf(b+1) - sumf(a));
  }
  return 0;
}
