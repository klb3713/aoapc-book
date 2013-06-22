// UVa10041 Vito's Family
// Rujia Liu
// 题意：输入r个正整数，找一个整数到所有整数的距离之和最少
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 500 + 5;

int main() {
  int T, n, a[maxn];
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    sort(a, a+n);
    int x = a[n/2], sum = 0;
    for(int i = 0; i < n; i++) sum += abs(x - a[i]);
    printf("%d\n", sum);
  }
  return 0;
}
