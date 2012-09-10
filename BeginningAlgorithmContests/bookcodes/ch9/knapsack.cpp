#include<cstdio>
#include<algorithm>
using namespace std;

#define MAXN 1000
#define MAXC 100000
int V[MAXN], W[MAXN];
int d[MAXN][MAXC];

int main() {
  int n, C;
  for(int i = 0; i < n; i++)
    scanf("%d%d", &V[i], &W[i]);

  for(int i = n; i >= 1; i--)
    for(int j = 0; j <= C; j++) {
      d[i][j] = (i==n ? 0 : d[i+1][j]);
      if(j >= V[i]) max(d[i][j], d[i+1][j-V[i]]+W[i]);
    }

  printf("%d\n", d[1][C]);
  return 0;
}
