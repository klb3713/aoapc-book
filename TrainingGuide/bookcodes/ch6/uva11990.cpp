// UVa11990 "Dynamic" Inversion
// Rujia Liu
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

inline int lowbit(int x) { return x&-x; }

struct Node {
  Node *ch[2]; // 左右子树
  int v; // 值
  int s; // 结点总数。有删除标记的结点未统计在内
  int d; // 删除标记
  Node():d(0) {}
  int ch_s(int d) { return ch[d] == NULL ? 0 : ch[d]->s; }
};

// 名次树，懒删除实现
struct RankTree {
  int n, next;
  int *v;
  Node *nodes, *root;
  RankTree(int n, int* A):n(n) {
    nodes = new Node[n];
    next = 0;
    v = new int[n];
    for(int i = 0; i < n; i++) v[i] = A[i];
    sort(v, v+n);
    root = build(0, n-1);
    delete[] v;
  }

  Node* build(int L, int R) {
    if(L > R) return NULL;
    int M = L + (R-L) / 2;
    int u = next++;
    nodes[u].v = v[M];
    nodes[u].ch[0] = build(L, M-1);
    nodes[u].ch[1] = build(M+1, R);
    nodes[u].s = nodes[u].ch_s(0) + nodes[u].ch_s(1) + 1;
    return &nodes[u];
  }

  // type = 0：统计比v小的元素个数
  // type = 1：统计比v大的元素个数  
  int count(int v, int type) {
    Node* u = root;
    int cnt = 0;
    while(u != NULL) {
      if(u->v == v) { cnt += u->ch_s(type); break; }
      int c = (v < u->v ? 0 : 1);
      if(c != type) cnt += u->s - u->ch_s(c);
      u = u->ch[c];
    }
    return cnt;
  }

  // 要保证v在树中且尚未删除
  void erase(int v) {
    Node* u = root;
    while(u != NULL) {
      u->s--;
      if(u->v == v) { assert(u->d == 0); u->d = 1; return; }
      int c = (v < u->v ? 0 : 1);
      u = u->ch[c];
    }
    assert(0);
  }

  ~RankTree() {
    delete[] nodes;
  }
};

// 嵌套名次树的Fenwick树
struct FenwickRankTree {
  int n;
  vector<RankTree*> C;

  void init(int n, int* A) {
    this->n = n;
    C.resize(n+1); // 存放在C[1]~C[n]
    for(int i = 1; i <= n; i++) {
      C[i] = new RankTree(lowbit(i), A+i-lowbit(i)+1);
    }
  }

  void clear() { for(int i = 1; i <= n; i++) delete C[i]; }

  // 统计A[1], A[2], ..., A[x]有多少个元素比v大(x<=n)
  int count(int x, int v, int type) {
    int ret = 0;
    while(x > 0) {
      ret += C[x]->count(v, type); x -= lowbit(x);
    }
    return ret;
  }

  // 删除A[x]=v
  void erase(int x, int v) {
    while(x <= n) {
      C[x]->erase(v); x += lowbit(x);
    }
  }
};

// 普通Fenwick树
struct FenwickTree {
  int n;
  vector<int> C;

  void init(int n) {
    this->n = n;
    C.resize(n+1);
    fill(C.begin(), C.end(), 0);
  }

  // 计算A[1]+A[2]+...+A[x] (x<=n)
  int sum(int x) {
    int ret = 0;
    while(x > 0) {
      ret += C[x]; x -= lowbit(x);
    }
    return ret;
  }

  // A[x] += d (1<=x<=n)
  void add(int x, int d) {
    while(x <= n) {
      C[x] += d; x += lowbit(x);
    }
  }
};

const int maxn = 200000 + 5;
const int maxm = 100000 + 5;
typedef long long LL;

int n, m, A[maxn], B[maxn], pos[maxn];
FenwickRankTree frt;
FenwickTree f; // 用来求逆序对数以及求已删除的元素有多少个比v小

LL inversion_pairs() {
  LL ans = 0;
  f.init(n);
  for(int i = n; i >= 1; i--) {
    ans += f.sum(A[i]-1);
    f.add(A[i], 1);
  }
  return ans;
}

int main() {
  while(scanf("%d%d", &n, &m) == 2) {
    for(int i = 1; i <= n; i++) {
      scanf("%d", &A[i]);
      pos[B[i] = A[i]] = i;
    }
    LL cnt = inversion_pairs();
    frt.init(n, A);
    f.init(n);
    for(int i = 0; i < m; i++) {
      printf("%lld\n", cnt);
      int x;
      scanf("%d", &x);
      f.add(x, 1);
      int a = frt.count(pos[x]-1, x, 1); // x左边有a个比x大
      int b = x-1; // 一共有x-1个数比x小
      int c = f.sum(x-1); // 删了c个比x小的
      int d = frt.count(pos[x]-1, x, 0);  // 现在左边有d个比x小
      b -= c + d;  // 还剩b个
      cnt -= a + b; // 逆序对减少a+b个
      frt.erase(pos[x], x);
    }
  }
  return 0;
}
