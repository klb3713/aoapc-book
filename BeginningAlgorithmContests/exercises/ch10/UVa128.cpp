// UVa128 Software CRC
// Rujia Liu
// 题意：输入一行字符串（可能为空，不含换行符），输出它的CRC。
// CRC定义：把每个字符看成是一位256进制数之后，再加两个字节之后使得能被34943整除。如有多解，加上的两个字节应尽量小。
// 算法：按照大数取余的方法求字符串后面加00 00之后除以34943的余数m，则m=0时答案为0，否则答案是34943-m。
#include<cstdio>
#include<cstring>
const int MOD = 34943;
const int maxn = 1024 + 10;
char s[maxn], buf[5];

int main() {
  while(fgets(s, maxn, stdin)) {
    if(s[0] == '#') break;
    int m = 0, n = strlen(s) - 1; // 减1是去掉回车符
    for(int i = 0; i < n; i++)
      m = (m * 256 + s[i]) % MOD;
    m = (long long)m * 65536 % MOD; // 注意乘以65536可能会溢出
    if(m > 0) m = MOD - m;
    sprintf(buf, "%04X", m);
    printf("%c%c %c%c\n", buf[0], buf[1], buf[2], buf[3]);
  }
  return 0;
}
