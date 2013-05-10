// UVa11205 The Broken Pedometer 
// Rujia Liu
// 题意：有P个LED灯，以及N个字符，要求选出个数最少的LED灯，使得即使只有这些灯正常工作，也能区分出这N个字符
// 题意抽象：输入两个整数P, N以及N行P列的01矩阵，找少的列，能区分所有行
// 规模：P<=15, N<=100
// 算法：2^P枚举。把每行理解为二进制整数可以简化代码
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 100 + 5;
int N, P, bits[maxn]; // bits[i]为第i个01串的整数值

// 判断子集S是否足以区分所有串
bool judge(int S) {
  for(int i = 0; i < N; i++)
    for(int j = 0; j < i; j++)
      if((bits[i] & S) == (bits[j] & S)) return false;
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &P, &N);
    for(int i = 0; i < N; i++) {
      int x = 0, b;
      for(int j = 0; j < P; j++) { scanf("%d", &b); x = x * 2 + b; }
      bits[i] = x;
    }

    int ans = P;
    for(int i = 0; i < (1<<P); i++) if(judge(i)) {      
      int cnt = 0;
      for(int j = 0; j < P; j++) if(i & (1<<j)) cnt++;
      ans = min(ans, cnt);
    }
    printf("%d\n", ans);
  }
  return 0;
}
