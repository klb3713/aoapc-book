#include<stdio.h>
#include<stdlib.h>
const int MAXN = 1000;
const int INF = 1000000000;
int G[MAXN][MAXN];

int main(int argc, char* argv[]) {
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      G[i][j] = INF;
  for(int i = 0; i < m; i++) {
    int u = rand() % n;
    int v = rand() % n;
    if(u != v)  G[u][v] = rand() % 1000;
  }
  m = 0;
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(G[i][j] < INF) m++;
  printf("%d %d\n", n, m);
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(G[i][j] < INF) printf("%d %d %d\n", i, j, G[i][j]);
  return 0;
}
