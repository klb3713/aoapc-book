#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int MAXN = 1000;
const int INF = 1000000000;
int cap[MAXN][MAXN], cost[MAXN][MAXN];

int main(int argc, char* argv[]) {
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  memset(cap, 0, sizeof(cap));
  for(int i = 0; i < m; i++) {
    int u = rand() % n;
    int v = rand() % n;
    if(u < v) {
      cap[u][v] = rand() % 1000 + 1;
      cost[u][v] = rand() % 1000 + 1;
    }
  }
  m = 0;
  for(int i = 0; i < n; i++)
    for(int j = i+1; j < n; j++)
      if(cap[i][j]) m++;
  printf("%d %d\n", n, m);
  for(int i = 0; i < n; i++)
    for(int j = i+1; j < n; j++)
      if(cap[i][j]) printf("%d %d %d %d\n", i, j, cap[i][j], cost[i][j]);
  return 0;
}
