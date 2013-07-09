// UVa11121 Base -2
// Rujia Liu
// 题意：已知正整数和负整数都有惟一的-2进制表示，而且不带符号位。输入整数n，输出它的-2进制表示
// 算法：按照b0, b1, ... 这样的顺序求解，每次对-2取余，然后把余数调整成0和1。
#include<cstdio>

void div_negative(int n, int m, int& q, int& r) {
  q = n / m;
  r = n - q * m;
  while(r < 0) { r -= m; q++; }
}

int b[10];
void solve(int n) {
  int k = 0, q, r;
  do {
    div_negative(n, -2, q, r);
    b[k++] = r;
    n = q;
  } while(n);
  for(int i = k-1; i >= 0; i--) printf("%d", b[i]);
  printf("\n");
}

int main() {
  int T, n, kase = 0;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    printf("Case #%d: ", ++kase);
    solve(n);
  }
  return 0;
}
