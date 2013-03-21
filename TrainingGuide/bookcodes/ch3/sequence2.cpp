// Fast Sequence Operations II
// Rujia Liu
// 输入格式：
// n m     数组范围是a[1]~a[n]，初始化为0。操作有m个
// 1 L R v 表示设a[L]=a[L+1]=...=a[R] = v。其中v > 0
// 2 L R   查询a[L]~a[R]的sum, min和max
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxnode = 1<<17;

int _sum, _min, _max, op, qL, qR, v;

struct IntervalTree {
  int sumv[maxnode], minv[maxnode], maxv[maxnode], setv[maxnode];

  // 维护信息
  void maintain(int o, int L, int R) {
    int lc = o*2, rc = o*2+1;
    if(R > L) {
      sumv[o] = sumv[lc] + sumv[rc];
      minv[o] = min(minv[lc], minv[rc]);
      maxv[o] = max(maxv[lc], maxv[rc]);
    }
    if(setv[o] >= 0) { minv[o] = maxv[o] = setv[o]; sumv[o] = setv[o] * (R-L+1); }
  }

  // 标记传递
  void pushdown(int o) {
    int lc = o*2, rc = o*2+1;
    if(setv[o] >= 0) { //本结点有标记才传递。注意本题中set值非负，所以-1代表没有标记
      setv[lc] = setv[rc] = setv[o];
      setv[o] = -1; // 清除本结点标记
    }
  }

  void update(int o, int L, int R) {
    int lc = o*2, rc = o*2+1;
    if(qL <= L && qR >= R) { // 标记修改
      setv[o] = v;
    } else {
      pushdown(o);
      int M = L + (R-L)/2;
      if(qL <= M) update(lc, L, M); else maintain(lc, L, M);
      if(qR > M) update(rc, M+1, R); else maintain(rc, M+1, R);
    }
    maintain(o, L, R);
  }

  void query(int o, int L, int R) {
    if(setv[o] >= 0) { // 递归边界1：有set标记
      _sum += setv[o] * (min(R,qR)-max(L,qL)+1);
      _min = min(_min, setv[o]);
      _max = max(_max, setv[o]);
    } else if(qL <= L && qR >= R) { // 递归边界2：边界区间
      _sum += sumv[o]; // 此边界区间没有被任何set操作影响
      _min = min(_min, minv[o]);
      _max = max(_max, maxv[o]);
    } else { // 递归统计
      int M = L + (R-L)/2;
      if(qL <= M) query(o*2, L, M);
      if(qR > M) query(o*2+1, M+1, R);
    }
  }
};

const int INF = 1000000000;

IntervalTree tree;

int main() {
  int n, m;
  while(scanf("%d%d", &n, &m) == 2) {
    memset(&tree, 0, sizeof(tree));
    memset(tree.setv, -1, sizeof(tree.setv));
    tree.setv[1] = 0;
    while(m--) {
      scanf("%d%d%d", &op, &qL, &qR);
      if(op == 1) {
        scanf("%d", &v);
        tree.update(1, 1, n);
      } else {
        _sum = 0; _min = INF; _max = -INF;
        tree.query(1, 1, n);
        printf("%d %d %d\n", _sum, _min, _max);
      }
    }
  }
  return 0;
}
