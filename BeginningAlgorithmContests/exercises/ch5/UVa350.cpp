// UVa350 Pseudo-Random Numbers
// Rujia Liu
// 题意：一种伪随机数发生器是利用递推式L' = (Z*L+I) mod M。输入Z, I, M, L，输出循环节长度
// 例如Z=7,I=5,M=12,L=4，产生序列为4, 9, 8, 1, 0, 5, 4, 9, ..., 答案为6
// 算法：注意到M<10000，直接用vis[x]表示x首次出现的位置

#include<cstdio>
#include<cstring>
const int maxn = 10000 + 5;
int vis[maxn];

int main() {
  int kase = 0, Z, I, M, L;
  while(scanf("%d%d%d%d", &Z, &I, &M, &L) == 4 && M) {
    memset(vis, 0, sizeof(vis));
    vis[L] = 1;
    for(int i = 1; ; i++) {
      L = (Z*L + I) % M;
      if(vis[L]) { printf("Case %d: %d\n", ++kase, i - vis[L] + 1); break; }
      vis[L] = i+1;
    }
  }
  return 0;
}
