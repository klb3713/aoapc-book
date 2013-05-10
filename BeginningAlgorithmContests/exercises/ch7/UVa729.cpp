// UVa729 The Hamming Distance Problem
// Rujia Liu
// 题意：
// 输入两个整数N, H，按照字典序输出所有长度为N，恰好包含H个1的01串
// 规模：1<=H<=N<=16
// 算法A：2^N枚举，输出1的个数为H的。采用递归枚举
#include <cstdio>
#include <cstring>
const int maxn = 20;
int N, H, bits[maxn];

// 从bits[d]开始确定，已经用了c0个0和c1个1
void gen(int d, int c0, int c1) {
  if(d == N) {
    if(c1 != H) return;
    for(int i = 0; i < N; i++) printf("%d", bits[i]);
    printf("\n");
  } else {
     bits[d] = 0; gen(d+1, c0+1, c1);
     bits[d] = 1; gen(d+1, c0, c1+1);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &N, &H);
    gen(0, 0, 0);
    if(T) printf("\n");
  }
  return 0;
}
