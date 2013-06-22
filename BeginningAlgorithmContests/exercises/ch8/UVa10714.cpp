// UVa10714 Ants
// Rujia Liu
// 题意：类似于《训练指南》中的蚂蚁问题，输入木板长度L和蚂蚁个数n，以及各个蚂蚁到木板左端点的位置。蚂蚁速度为1，求最短时间和最长时间
// 算法：
#include<cstdio>
#include<algorithm>
using namespace std;

int main() {
  int T, L, n, x;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &L, &n);
    int mint = 0, maxt = 0;
    for(int i = 0; i < n; i++) {
      scanf("%d", &x);
      mint = max(mint, min(x, L-x));
      maxt = max(maxt, max(x, L-x));
    }
    printf("%d %d\n", mint, maxt);
  }
  return 0;
}
