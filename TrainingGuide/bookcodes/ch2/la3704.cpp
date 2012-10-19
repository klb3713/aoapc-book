// LA3704 Cellular Automaton
// Rujia Liu
#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;

int MOD;

typedef vector<int> CirculantMatrix;

CirculantMatrix operator * (const CirculantMatrix& a, const CirculantMatrix& b) {
  int n = a.size();
  assert(b.size() == n);
  CirculantMatrix c(n);
  for(int i = 0; i < n; i++) { // 计算C(0,i)
    c[i] = 0;
    for(int j = 0; j < n; j++) // 累加A(0,j)*B(j,i)
      c[i] = ((long long)a[j]*b[(i-j+n)%n] + c[i]) % MOD; // 第j行是由第0行循环右移j位得到
  }
  return c;
}

// 计算a^k的值。要求a支持*运算符
template<typename T>
T fast_pow(const T& a, int k) {
  assert(k > 0);
  if(k == 1) return a;
  T b = fast_pow(a, k/2);
  b = b * b;
  if(k % 2 == 1) b = b * a;
  return b;
}

int main() {
  int n, m, d, k;
  while(scanf("%d%d%d%d", &n, &m, &d, &k) == 4) {
    MOD = m;
    CirculantMatrix mat(n);
    for(int i = 0; i < n; i++)
      mat[i] = min(i, n - i) <= d ? 1 : 0; // 离格子0的距离<=d的位置系数设为1，其余为0

    CirculantMatrix v(n); // 可以把初始状态当作循环矩阵进行计算
    for(int i = 0; i < n; i++) scanf("%d", &v[i]);
    v = v * fast_pow(mat, k);

    printf("%d", v[0]);
    for(int i = 1; i < n; i++) printf(" %d", v[i]);
    printf("\n");
  }
  return 0;
}
