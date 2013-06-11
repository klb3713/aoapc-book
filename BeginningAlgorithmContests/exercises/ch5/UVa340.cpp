// UVa340 Master-Mind Hints
// Rujia Liu
// 题意：实现一个经典“猜数字”游戏。给定答案序列和用户猜的序列，统计有多少数字位置正确（A），有多少数字在两个序列都出现过但位置不对（B）
// 算法：直接统计可得A，为了求B，对于每个数字（1~9），统计在二者出现的次数c1和c2，则min(c1,c2)就是该数字对B的贡献。最后要减去A的部分
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 10;

int main() {
  int n, a[maxn], b[maxn];
  int kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    printf("Game %d:\n", ++kase);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    for(;;) {
      int A = 0, B = 0;
      for(int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        if(a[i] == b[i]) A++;
      }
      if(b[0] == 0) break;
      for(int d = 1; d <= 9; d++) {
        int c1 = 0, c2 = 0;
        for(int i = 0; i < n; i++) {
          if(a[i] == d) c1++;
          if(b[i] == d) c2++;
        }
        B += min(c1, c2);
      }
      printf("    (%d,%d)\n", A, B-A);
    }
  }
  return 0;
}
