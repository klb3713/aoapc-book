// UVa133 The Dole Queue
// Rujia Liu
/*
  题意：
  n<20个人站成一圈，逆时针编号为1~n。
  有两个官员，A从1开始逆时针数，B从n开始顺时针数。
  在每一轮中，官员A数k个就停下来，B数m个就停下来（注意有可能两个官员停在同一个人上）。
  接下来被官员选中的人（1个或者2个）离开队伍

  输入n, k, m, 输出每轮里被选中的人的编号（如果有两个人，先输出被A选中的）

  算法：因为规模小，直接模拟即可。用0表示离开队伍的人，数数的时候跳过
*/
#include<cstdio>
const int maxn = 25;
int n, k, m, a[maxn];

// 逆时针走t步，步长是d（-1表示顺时针走）
void go(int& p, int d, int t) {
  while(t--) {
    do { p = (p+d+n-1) % n + 1; } while(a[p] == 0); // 走到下一个非0数字
  }
}

int main() {
  while(scanf("%d%d%d", &n, &k, &m) == 3 && n) {
    for(int i = 1; i <= n; i++) a[i] = i;
    int left = n; // 还剩下的人数
    int p1 = n, p2 = 1;
    while(left) {
      go(p1, 1, k);
      go(p2, -1, m);
      printf("%3d", p1); left--;
      if(p2 != p1) { printf("%3d", p2); left--; }
      a[p1] = a[p2] = 0;
      if(left) printf(",");
    }
    printf("\n");
  }  
  return 0;
}
