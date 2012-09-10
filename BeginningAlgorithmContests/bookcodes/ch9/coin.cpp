#include<cstdio>
#include<algorithm>
using namespace std;

#define MaxN 105
#define INF 1000000000
int V[MaxN], Min[MaxN], Max[MaxN];
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
  Min[0] = Max[0] = 0;
  for(int i = 1; i <= S; i++) {
    Min[i] = INF;
    Max[i] = -INF;
  }
  for(int i = 1; i <= S; i++)
    for(int j = 1; j <= n; j++)
      if(i >= V[j]) {
        Min[i] = min(Min[i], Min[i-V[j]] + 1);
        Max[i] = max(Max[i], Max[i-V[j]] + 1);
      }
  printf("%d %d\n", Min[S], Max[S]);
  print_ans(Min, S);
  printf("\n");
  print_ans(Max, S);
  printf("\n");
  return 0;
}
