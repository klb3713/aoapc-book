// UVa270 Lining Up
// Rujia Liu
// 题意：输入平面上n个不同点，判断最多有几个点在同一条直线上
// 算法：枚举起点，算其他所有点到它的斜率，最后排序后扫描，看有多少个相同
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 700;
const double eps = 1e-6;
int x[maxn], y[maxn];
double ang[maxn];

int main() {
  int T;
  scanf("%d\n", &T);
  while(T--) {
    int n = 0;
    char buf[100];
    for(;;) {
      if(fgets(buf, maxn, stdin) == NULL) break;
      if(sscanf(buf, "%d%d", &x[n], &y[n]) != 2) break;
      n++;
    }

    int ans = 1;
    for(int i = 0; i < n; i++) {
      int k = 0;
      for(int j = 0; j < n; j++)
        if(i != j) ang[k++] = atan2(y[j]-y[i], x[j]-x[i]);
      sort(ang, ang+k);
      int cnt = 1;
      for(int j = 1; j < k; j++) {
        if(fabs(ang[j] - ang[j-1]) < eps) cnt++; else cnt = 1;
        ans = max(ans, cnt+1);
      }
    }
    printf("%d\n", ans);
    if(T) printf("\n");
  }
  return 0;
}
