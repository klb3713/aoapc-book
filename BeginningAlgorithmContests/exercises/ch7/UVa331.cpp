// UVa331 Mapping the Swaps
// Rujia Liu
// 题意：给n(n<=5)个整数，每次可以交换两个相邻数，设最少需要交换d次。求有多少种方案的交换次数为d？
// 算法：d为逆序对数，然后回溯即可。

#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 10;
int n, inv, ans, a[maxn];

void dfs(int d) {
  if(d == inv) {
    for(int i = 0; i < n-1; i++) if(a[i] > a[i+1]) return;
    ans++;
  } else for(int i = 0; i < n-1; i++) {
    swap(a[i], a[i+1]);
    dfs(d+1);
    swap(a[i], a[i+1]);
  }
}

int main() {
  int kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    inv = 0;
    for(int i = 0; i < n; i++)
      for(int j = i+1; j < n; j++) if(a[i] > a[j]) inv++;
    ans = 0;
    if(inv > 0) dfs(0);
    printf("There are %d swap maps for input data set %d.\n", ans, ++kase);
  }  
  return 0;
}
