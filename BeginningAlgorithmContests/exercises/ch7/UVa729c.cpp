// UVa729 The Hamming Distance Problem
// Rujia Liu
// 题意：
// 输入两个整数N, H，按照字典序输出所有长度为N，恰好包含H个1的01串
// 规模：1<=H<=N<=16
// 算法C：C(N,H)枚举，枚举的对象为0，所以枚举顺序就是字典序
#include <cstdio>
#include <cstring>
const int maxn = 20;
int N, H, zero[maxn]; // zero[i]为第i为是否为0

// 从第d个0的位置开始确定，取值范围是from~N-1
void gen(int d, int from) {
  if(d == N-H) {
    for(int i = 0; i < N; i++) printf("%d", zero[i] ? 0 : 1);
    printf("\n");
  } else {
     for(int i = from; i < N; i++) {
       zero[i] = 1;
       gen(d+1, i+1);
       zero[i] = 0;
     }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &N, &H);
    memset(zero, 0, sizeof(zero));
    gen(0, 0);
    if(T) printf("\n");
  }
  return 0;
}
