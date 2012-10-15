// UVa11825 Hacker's Crackdown
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 16;
int n, P[maxn], cover[1<<maxn], f[1<<maxn];
int main() {
  int kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    for(int i = 0; i < n; i++) {
      int m, x;
      scanf("%d", &m);
      P[i] = 1<<i;
      while(m--) { scanf("%d", &x); P[i] |= (1<<x); }
    }
    for(int S = 0; S < (1<<n); S++) {
      cover[S] = 0;
      for(int i = 0; i < n; i++)
        if(S & (1<<i)) cover[S] |= P[i];
    }
    f[0] = 0;
    int ALL = (1<<n) - 1;
    for(int S = 1; S < (1<<n); S++) {
      f[S] = 0;
      for(int S0 = S; S0; S0 = (S0-1)&S)
        if(cover[S0] == ALL) f[S] = max(f[S], f[S^S0]+1);
    }
    printf("Case %d: %d\n", ++kase, f[ALL]);
  }
  return 0;
}
