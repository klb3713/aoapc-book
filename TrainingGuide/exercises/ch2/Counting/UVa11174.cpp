// UVa11174 Stand in a Line
// Rujia Liu

int mul_mod(int a, int b, int n) {
  a %= n; b %= n;
  return (int)((long long)a * b % n);
}

void gcd(int a, int b, int& d, int& x, int& y) {
  if(!b){ d = a; x = 1; y = 0; }
  else{ gcd(b, a%b, d, y, x); y -= x*(a/b); }
}

int inv(int a, int n) {
  int d, x, y;
  gcd(a, n, d, x, y);
  return d == 1 ? (x%n+n)%n : -1;
}

#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

const int maxn = 40000 + 10;
const int MOD = 1000000007;

vector<int> sons[maxn];
int fa[maxn], fac[maxn], ifac[maxn];

int mul_mod(int a, int b) {
  return mul_mod(a, b, MOD);
}

// fac[i] = (i!)%MOD, ifac[i]为fac[i]在模MOD下的逆
void preprocess() {
  fac[0] = ifac[0] = 1;
  for(int i = 1; i < maxn; i++) {
    fac[i] = mul_mod(fac[i-1], i);
    ifac[i] = inv(fac[i], MOD);
  }
}

// 组合数C(n,m)除以MOD的余数
int C(int n, int m) {
  return mul_mod(mul_mod(fac[n], ifac[m]), ifac[n-m]);
}

// 统计以u为根的子树有多少种排列。size为该子树的结点总数
int count(int u, int& size) {
  int d = sons[u].size();
  vector<int> sonsize; // 各子树的大小
  size = 1;
  int ans = 1;
  for(int i = 0; i < d; i++) {
    int sz;
    ans = mul_mod(ans, count(sons[u][i], sz));
    size += sz;
    sonsize.push_back(sz);
  }
  int sz = size-1; // 非根结点的个数
  for(int i = 0; i < d; i++) {
    ans = mul_mod(ans, C(sz, sonsize[i]));
    sz -= sonsize[i];
  }
  return ans;
}

int main() {
  int T;
  scanf("%d", &T);
  preprocess();  
  while(T--) {
    int n, m;
    scanf("%d%d", &n, &m);
    memset(fa, 0, sizeof(fa));
    for(int i = 0; i <= n; i++) sons[i].clear();
    for(int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      fa[a] = b;
      sons[b].push_back(a);
    }
    // 没有父亲的结点称为虚拟结点的儿子
    for(int i = 1; i <= n; i++)
      if(!fa[i]) sons[0].push_back(i);
    int size;
    printf("%d\n", count(0, size));
  }
  return 0;
}
