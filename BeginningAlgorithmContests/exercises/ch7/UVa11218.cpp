// UVa11218 KTV
// Rujia Liu
// 题意：给出n个带权集合，每个集合包含1~9中的三个整数。找出其中三个集合，使得1~9恰好各出现一次，且权和最大
// 算法：暴力n^2枚举前两个集合，直接计算出第三个集合。用位运算让代码更简单，速度也更快

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 10;
const int ALL = (1<<9)-1;
int mask[maxn], v[ALL+1];

int main() {
  int kase = 0, n;
  while(scanf("%d", &n) == 1 && n) {
    memset(v, 0, sizeof(v));
    for(int i = 0; i < n; i++) {
      int a, b, c, s;
      scanf("%d%d%d%d", &a, &b, &c, &s); a--; b--; c--;
      mask[i] = (1<<a) + (1<<b) + (1<<c);
      v[mask[i]] = max(v[mask[i]], s);
    }

    int ans = -1;
    for(int i = 0; i < n; i++)
      for(int j = i+1; j < n; j++) if((mask[i] & mask[j]) == 0) {
        int last_mask = ALL ^ mask[i] ^ mask[j]; // 最后一个组合的mask
        if(v[last_mask]) ans = max(ans, v[mask[i]] + v[mask[j]] + v[last_mask]);
      }
    printf("Case %d: %d\n", ++kase, ans);
  }
  return 0;
}
