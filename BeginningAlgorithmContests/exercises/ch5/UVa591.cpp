// UVa591 Box of Bricks
// Rujia Liu
// 题意：有n列砖，第i列有h[i]个砖。总砖数是n的整数倍。最少移动多少块砖，使得每列砖的个数相同？
// 算法：贪心。先算平均数，所有多的砖都拿出来，补齐剩下的

#include<cstdio>
const int maxn = 50 + 5;
int h[maxn];

int main() {
  int kase = 0, n;
  while(scanf("%d", &n) == 1 && n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
      scanf("%d", &h[i]);
      sum += h[i];
    }
    int avg = sum / n, ans = 0;
    for(int i = 0; i < n; i++)
      if(h[i] > avg) ans += h[i] - avg;
    printf("Set #%d\nThe minimum number of moves is %d.\n\n", ++kase, ans);
  }
  return 0;
}
