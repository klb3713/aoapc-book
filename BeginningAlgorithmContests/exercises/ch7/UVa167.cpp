// UVa167 The Sultan's Successors
// Rujia Liu
// 题意：八皇后问题的扩展。8*8棋盘上每个格子都有一个整数，要求8个皇后所在格子的数字之后最大
// 算法：枚举全排列，然后判断是否有两个皇后在同一条对角线上

#include<cstdio>
#include<algorithm>
using namespace std;
int v[8][8], P[8];

bool judge() {
  bool ok = true;
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < i; j++)
     if(P[i]-i == P[j]-j || P[i]+i == P[j]+j) return false;
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    for(int i = 0; i < 8; i++) {
      P[i] = i;
      for(int j = 0; j < 8; j++)
        scanf("%d", &v[i][j]);
    }
    int ans = 0;
    do {
      if(!judge()) continue;
      int sum = 0;
      for(int i = 0; i < 8; i++) sum += v[i][P[i]];
      ans = max(ans, sum);
    } while(next_permutation(P, P+8));
    printf("%5d\n", ans);
  }
  return 0;
}
