// UVa11462 Age Sort
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<cctype> // 为了使用isdigit宏

inline int readint() {
  char c = getchar();
  while(!isdigit(c)) c = getchar();

  int x = 0;
  while(isdigit(c)) {
    x = x * 10 + c - '0';
    c = getchar();
  }    
  return x;
}

int buf[10]; // 声明成全局变量可以减小开销
inline void writeint(int i) {
  int p = 0;
  if(i == 0) p++; // 特殊情况：i等于0的时候需要输出0，而不是什么也不输出
  else while(i) {
    buf[p++] = i % 10;
    i /= 10;
  }
  for(int j = p-1; j >=0; j--) putchar('0' + buf[j]); // 逆序输出
}

int main() {
  int n, x, c[101];
  while(n = readint()) {
    memset(c, 0, sizeof(c));
    for(int i = 0; i < n; i++) c[readint()]++;
    int first = 1;
    for(int i = 1; i <= 100; i++)
      for(int j = 0; j < c[i]; j++) {
        if(!first) putchar(' ');
        first = 0;
        writeint(i);
      }
    putchar('\n');
  }
  return 0;
}
