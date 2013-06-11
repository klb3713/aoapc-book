// UVa575 Skew Binary
// Rujia Liu
// 题意：输入一个Skew Binary，转化成10进制。Skew Binary的右数第k位（k>=0）代表2^(k+1)-1

#include<cstdio>
#include<cstring>
const int maxn = 100;

int main() {
  char s[maxn];
  while(scanf("%s", s) == 1) {
    int n = strlen(s);
    if(n == 1 && s[0] == '0') break;
    long long v = 0;
    for(int k = 0; k < n; k++)
      v += (s[n-1-k] - '0') * ((1<<(k+1)) - 1);
    printf("%lld\n", v);
  }
  return 0;
}
