#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
const int MAXN = 1000;

int n, m;
int v[MAXN], d[MAXN], G[MAXN][MAXN];

int main() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      G[i][j] = INF;
  for(int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    G[u][v] = w;
  }
  memset(v, 0, sizeof(v));
  for(int i = 0; i < n; i++) d[i] = (i==0 ? 0 : INF);
  for(int i = 0; i < n; i++) {
    int x, m = INF;
    for(int y = 0; y < n; y++) if(!v[y] && d[y]<=m) m = d[x=y];
    v[x] = 1;
    for(int y = 0; y < n; y++) d[y] = min(d[y], d[x] + G[x][y]);
  }
  for(int i = 0; i < n; i++)
    printf("%d\n", d[i]);
  return 0;
}
