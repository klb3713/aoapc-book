// LA4513 Stammering Aliens
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 40000 + 10;
const int x = 123;
int n, m, pos;
unsigned long long H[maxn], xp[maxn];

unsigned long long hash[maxn];
int rank[maxn];

int cmp(const int& a, const int& b) {
  return hash[a] < hash[b] || (hash[a] == hash[b] && a < b);
}

int possible(int L) {
  int c = 0;
  pos = -1;
  for(int i = 0; i < n-L+1; i++) {
    rank[i] = i;
    hash[i] = H[i] - H[i+L]*xp[L];
  }
  sort(rank, rank+n-L+1, cmp);
  for(int i = 0; i < n-L+1; i++) {
    if(i == 0 || hash[rank[i]] != hash[rank[i-1]]) c = 0;
    if(++c >= m) pos = max(pos, rank[i]);
  }
  return pos >= 0;
}

int main() {
  char s[maxn];
  while(scanf("%d", &m) == 1 && m) {
    scanf("%s", s);
    n = strlen(s);

    H[n] = 0;
    for(int i = n-1; i >= 0; i--) H[i] = H[i+1]*x + (s[i] - 'a');
    xp[0] = 1;
    for(int i = 1; i <= n; i++) xp[i] = xp[i-1]*x;

    if(!possible(1)) printf("none\n");
    else {
      int L = 1, R = n+1;
      while(R - L > 1) {
        int M = L + (R-L)/2;
        if(possible(M)) L = M; else R = M;
      }
      possible(L);
      printf("%d %d\n", L, pos);
    }
  }
  return 0;
}
