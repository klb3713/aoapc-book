#include<stdio.h>
#define MAXN 105
#define INF 1000000000
int V[MAXN], min[MAXN], max[MAXN], min_coin[MAXN], max_coin[MAXN];
int n, S;

void print_ans(int* d, int S) {
  while(S) {
    printf("%d ", d[S]);
    S -= V[d[S]];
  }
}

int main() {
  scanf("%d%d", &n, &S);
  for(int i = 1; i <= n; i++) scanf("%d", &V[i]);
  min[0] = max[0] = 0;
  for(int i = 1; i <= S; i++) {
    min[i] = INF;
    max[i] = -INF;
  }
  for(int i = 1; i <= S; i++)
    for(int j = 1; j <= n; j++)
      if(i >= V[j]) {
        if(min[i] > min[i-V[j]] + 1) {
          min[i] = min[i-V[j]] + 1;
          min_coin[i] = j;
        }
        if(max[i] < max[i-V[j]] + 1) {
          max[i] = max[i-V[j]] + 1;
          max_coin[i] = j;
        }
      }
  printf("%d %d\n", min[S], max[S]);
  print_ans(min_coin, S);
  printf("\n");
  print_ans(max_coin, S);
  printf("\n");
  return 0;
}
