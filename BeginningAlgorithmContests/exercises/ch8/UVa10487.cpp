// UVa10487 Closest Sums
// Rujia Liu
// 题意：输入n个数以及m个查询，每次查询一个数x，需要在n个数中找到两个数之和尽量接近x
// 算法：二分查找。lower_bound返回大于或等于x的第一个位置
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;
int a[maxn], s[maxn*maxn];

int main() {
  int n, m, k, x, kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    k = 0;
    for(int i = 0; i < n; i++)
      for(int j = i+1; j < n; j++) s[k++] = a[i]+a[j];
    sort(s, s+k);
    k = unique(s, s+k) - s;
    printf("Case %d:\n", ++kase);
    scanf("%d", &m);
    while(m--) {
      scanf("%d", &x);
      int p = lower_bound(s, s+k, x) - s;
      int ans;
      if(p == 0 || (p < k && s[p] - x < x - s[p-1])) ans = s[p]; else ans = s[p-1];
      printf("Closest sum to %d is %d.\n", x, ans);
    }
  }
  return 0;
}
