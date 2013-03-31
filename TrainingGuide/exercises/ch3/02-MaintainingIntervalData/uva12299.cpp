// UVa12299 RMQ with Shifts
// Rujia Liu
#include<cstdio>
#include<cctype>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
const int maxnode = 1<<18;

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
const int maxn = 100000 + 10;
int A[maxn];

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  memset(&tree, 0, sizeof(tree));
  for(p = 1; p <= n; p++) {
    scanf("%d", &v);
    A[p] = v;
    tree.update(1, 1, n);
  }
  int k, args[20], original[20];
  char cmd[100];
  while(q--) {
    scanf("%s", cmd);

    // 解析输入
    int len = strlen(cmd);
    k = 0; args[k] = 0;
    for(int i = 6; i < len; i++)
      if(isdigit(cmd[i])) args[k] = args[k] * 10 + cmd[i] - '0';
      else { k++; args[k] = 0; }

    // 处理命令
    if(cmd[0] == 'q') {
      qL = args[0]; qR = args[1];
      printf("%d\n", tree.query(1, 1, n));
    } else {
      for(int i = 0; i < k; i++) original[i] = A[args[i]];
      for(int i = 0; i < k; i++) {
        p = args[i];
        v = A[p] = original[(i+1)%k];
        tree.update(1, 1, n);
      }
    }
  }
  return 0;
}
