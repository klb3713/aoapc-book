// UVa152 Tree's a Crowd
// Rujia Liu
// 题意：输入n个三维点，计算每个点i到最近点的距离d[i]，统计d[i]在[0,1), [1,2), [2,3), ..., [9,10)的点的个数

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 5000 + 10;
int x[maxn], y[maxn], z[maxn];
int cnt[10]; // cnt[i]就是到最近点距离在[i,i+1)的点的个数

int main() {
  int n = 0;
  for(;;) {
    scanf("%d%d%d", &x[n], &y[n], &z[n]);
    if(x[n] == 0 && y[n] == 0 && z[n] == 0) break;
    n++;
  }
  memset(cnt, 0, sizeof(cnt));
  for(int i = 0; i < n; i++) {
    int mind2 = 1000000000; // mind2是点i到最近点距离的平方
    for(int j = 0; j < n; j++) if(i != j)
      mind2 = min(mind2, (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) + (z[i]-z[j])*(z[i]-z[j]));
    for(int j = 0; j < 10; j++)
      if(mind2 >= j*j && mind2 < (j+1)*(j+1)) cnt[j]++;
  }
  for(int i = 0; i < 10; i++) printf("%4d", cnt[i]);
  printf("\n");
  return 0;
}
