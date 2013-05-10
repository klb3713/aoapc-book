// UVa729 The Hamming Distance Problem
// Rujia Liu
// 题意：
// 输入两个整数N, H，按照字典序输出所有长度为N，恰好包含H个1的01串
// 规模：1<=H<=N<=16
// 算法B：2^N枚举，输出1的个数为H的，采用直接枚举子集
#include <cstdio>
#include <cstring>
int N, H;

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &N, &H);
    for(int i = 0; i < (1<<N); i++) {
      int cnt = 0;
      for(int j = 0; j < N; j++) if(i & (1<<j)) cnt++;
      if(cnt == H) {
        for(int j = N-1; j >= 0; j--) printf("%d", (i & (1<<j)) ? 1 : 0); 
        printf("\n");
      }
    }
    if(T) printf("\n");
  }
  return 0;
}
