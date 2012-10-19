// LA3644 X-Plosives
// Rujia Liu
#include <cstdio>
const int maxn = 100000 + 10;
int pa[maxn];

// 并查集的查找操作，带路径压缩
int findset(int x) { return pa[x] != x ? pa[x] = findset(pa[x]) : x; } 

int main() {
  int x, y;
  while(scanf("%d", &x) == 1) {
    for(int i = 0; i <= maxn; i++) pa[i] = i;
    int refusals = 0;
    while(x != -1) {
      scanf("%d", &y);
      x = findset(x); y = findset(y);
      if(x == y) ++refusals; // 如果x和y在同一个集合，则拒绝
      else pa[x] = y; // 否则合并。这里没有使用启发式合并
      scanf("%d", &x);
    }
    printf("%d\n", refusals);
  }
  return 0;
}
