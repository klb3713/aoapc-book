// UVa299 Train Swapping
// Rujia Liu
// 题意：输入n的一个全排列，每次可以交换相邻两个数，最少要几次才能变成升序排列？
// 算法：逆序对数
#include<cstdio>
const int maxn = 100;
int main() {
  int T, n, a[maxn];
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    int cnt = 0;
    for(int i = 0; i < n; i++)
      for(int j = i+1; j < n; j++) if(a[i] > a[j]) cnt++;
    printf("Optimal train swapping takes %d swaps.\n", cnt);
  }
  return 0;
}
