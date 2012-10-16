// UVa10828 Back to Kernighan-Ritchie
// Rujia Liu
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

const double eps = 1e-8;
const int maxn = 100 + 10;
typedef double Matrix[maxn][maxn];

// 由于本题的特殊性，消元后不一定是对角阵，甚至不一定是阶梯阵
// 但若x[i]解惟一且有限，第i行除了A[i][i]和A[i][n]之外的其他元素均为0
void gauss_jordan(Matrix A, int n) {
  int i, j, k, r;
  for(i = 0; i < n; i++) {
    r = i;
    for(j = i+1; j < n; j++)
      if (fabs(A[j][i]) > fabs(A[r][i])) r = j;
    if(fabs(A[r][i]) < eps) continue; // 放弃这一行，直接处理下一行 (*)
    if(r != i) for(j = 0; j <= n; j++) swap(A[r][j], A[i][j]);

    // 与除了第i行外的其他行进行消元
    for(k = 0; k < n; k++) if(k != i)
      for(j = n; j >= i; j--) A[k][j] -= A[k][i]/A[i][i] * A[i][j];
  }
}

Matrix A;
int n, d[maxn];
vector<int> prev[maxn];
int inf[maxn];

int main() {
  int kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    memset(d, 0, sizeof(d));
    for(int i = 0; i < n; i++) prev[i].clear();

    int a, b;
    while(scanf("%d%d", &a, &b) == 2 && a) {
      a--; b--; // 改成从0开始编号
      d[a]++; // 结点a的出度加1
      prev[b].push_back(a);
    }

    // 构造方程组
    memset(A, 0, sizeof(A));
    for(int i = 0; i < n; i++) {
      A[i][i] = 1;
      for(int j = 0; j < prev[i].size(); j++)
        A[i][prev[i][j]] -= 1.0 / d[prev[i][j]];
      if(i == 0) A[i][n] = 1;
    }

    // 解方程组，标记无穷变量
    gauss_jordan(A, n);
    memset(inf, 0, sizeof(inf));
    for(int i = n-1; i >= 0; i--) {
      if(fabs(A[i][i])<eps && fabs(A[i][n])>eps) inf[i] = 1; // 直接解出来的无穷变量
      for(int j = i+1; j < n; j++)
        if(fabs(A[i][j])>eps && inf[j]) inf[i] = 1; // 和无穷变量扯上关系的变量也是无穷的
    }

    int q, u;
    scanf("%d", &q);
    printf("Case #%d:\n", ++kase);
    while(q--) {
      scanf("%d", &u); u--;
      if(inf[u]) printf("infinity\n");
      else printf("%.3lf\n", fabs(A[u][u])<eps ? 0.0 : A[u][n]/A[u][u]);
    }
  }
  return 0;
}
