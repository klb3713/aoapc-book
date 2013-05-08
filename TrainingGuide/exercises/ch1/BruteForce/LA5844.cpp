// LA5844/UVa1509 Leet
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;

int n, m, k;
char s[20], t[50];
int st[256], L[256];

// match s[d:] and t[p:]
int dfs(int d, int p) {
  if(p > m) return 0;
  if(d == n) return p == m ? 1 : 0;
  if(m - p < (n-d) || m - p > (n-d)*k) return 0;

  if(L[s[d]] > 0) {
    for(int i = 0; i < L[s[d]]; i++)
      if(t[st[s[d]] + i] != t[p + i]) return 0;
    return dfs(d+1, p + L[s[d]]);
  }
  for(int i = 1; i <= k; i++) {
    st[s[d]] = p;
    L[s[d]] = i;
    if(dfs(d+1, p+i)) return 1;
    L[s[d]] = 0;
  }
  return 0;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &k);
    scanf("%s%s", s, t);
    n = strlen(s);
    m = strlen(t);
    memset(L, 0, sizeof(L));
    int res = dfs(0, 0);
    printf("%d\n", res);
  }
  return 0;
}
