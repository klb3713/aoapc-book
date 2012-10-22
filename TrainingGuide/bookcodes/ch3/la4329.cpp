// LA4329 Ping pong
// Rujia Liu
#include<cstdio>
#include<vector>
using namespace std;

//inline int lowbit(int x) { return x&(x^(x-1)); }
inline int lowbit(int x) { return x&-x; }

struct FenwickTree {
  int n;
  vector<int> C;

  void resize(int n) { this->n = n; C.resize(n); }
  void clear() { fill(C.begin(), C.end(), 0); }

  // º∆À„A[1]+A[2]+...+A[x] (x<=n)
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

const int maxn = 20000 + 5;
int n, a[maxn], c[maxn], d[maxn];
FenwickTree f;

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &n);
    int maxa = 0;
    for(int i = 1; i <= n; i++) { scanf("%d", &a[i]); maxa = max(maxa, a[i]); }
    f.resize(maxa);
    f.clear();
    for(int i = 1; i <= n; i++) {
      f.add(a[i], 1);
      c[i] = f.sum(a[i]-1);
    }
    f.clear();
    for(int i = n; i >= 1; i--) {
      f.add(a[i], 1);
      d[i] = f.sum(a[i]-1);
    }

    long long ans = 0;
    for(int i = 1; i <= n; i++)
      ans += (long long)c[i]*(n-i-d[i]) + (long long)(i-c[i]-1)*d[i];
    printf("%lld\n", ans);
  }
  return 0;
}
