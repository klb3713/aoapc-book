// Dynamic RMQ
// Rujia Liu
// 输入格式：
// n m     数组范围是a[1]~a[n]，初始化为0。操作有m个
// 1 p v   表示设a[p]=v
// 2 L R   查询a[L]~a[R]的min
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
const int maxnode = 1<<17;

int op, qL, qR, p, v;

struct IntervalTree {
  int minv[maxnode];

  void update(int o, int L, int R) {
    int M = L + (R-L)/2;
    if(L == R) minv[o] = v; // 叶结点，直接更新minv
    else {
      // 先递归更新左子树或右子树
      if(p <= M) update(o*2, L, M); else update(o*2+1, M+1, R);
      // 然后计算本结点的minv
      minv[o] = min(minv[o*2], minv[o*2+1]);
    }
  }

  int query(int o, int L, int R) {
    int M = L + (R-L)/2, ans = INF;
    if(qL <= L && R <= qR) return minv[o]; // 当前结点完全包含在查询区间内
    if(qL <= M) ans = min(ans, query(o*2, L, M)); // 往左走
    if(M < qR) ans = min(ans, query(o*2+1, M+1, R)); // 往右走
    return ans;
  }
};


IntervalTree tree;

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2) {
    memset(&tree, 0, sizeof(tree));
    while(m--) {
      scanf("%d", &op);
      if(op == 1) {
        scanf("%d%d", &p, &v);
        tree.update(1, 1, n);
      } else {
        scanf("%d%d", &qL, &qR);
        printf("%d\n", tree.query(1, 1, n));
      }
    }
  }
  return 0;
}
