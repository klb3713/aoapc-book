// UVa11100 The Trip, 2007
// Rujia Liu
// 题意：现在有一系列的包裹，形状都是一样的，所以小包可以套在大包的里面，这样包就少了一个。给出一系列大小不同的包，要求设计一种互相套起来的方案，使最后留下的piece最少。在此前提下piece里包数的最大值应尽量小 
// 算法：注意大小相同的包不能相互套，假设大小为s的包有cnt[s]个，则max{cnt[s]}就是答案。方案构造也不难：排序以后循环给piece 1, 2, 3, ..., k
#include<cstdio>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 5;
int s[maxn];

int main() {
  int n, kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    int ans = 1, cnt = 1;
    for(int i = 0; i < n; i++) scanf("%d", &s[i]);
    sort(s, s+n);
    for(int i = 1; i < n; i++) {
      if(s[i] != s[i-1]) cnt = 1;
      else ans = max(ans, ++cnt);
    }

    if(kase++ > 0) printf("\n");
    printf("%d\n", ans);
    for(int i = 0; i < ans; i++) {
      for(int j = i; j < n; j += ans) {
        if(j > i) printf(" ");
        printf("%d", s[j]);
      }
      printf("\n");
    }
  }
  return 0;
}
