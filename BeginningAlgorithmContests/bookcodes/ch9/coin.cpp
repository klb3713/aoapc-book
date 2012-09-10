#include<stdio.h>
#define MAXN 105
#define INF 1000000000
int V[MAXN], min[MAXN], max[MAXN];
int n, S;

void print_ans(int* d, int S) {
  for(int i = 1; i <= n; i++)
    if(S>=V[i] && d[S]==d[S-V[i]]+1) {
      printf("%d ", i);
      print_ans(d, S-V[i]);
      break;
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
        min[i] <?= min[i-V[j]] + 1;
        max[i] >?= max[i-V[j]] + 1;
      }
  printf("%d %d\n", min[S], max[S]);
  print_ans(min, S);
  printf("\n");
  print_ans(max, S);
  printf("\n");
  return 0;
}
