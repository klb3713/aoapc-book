#include<stdio.h>
const int MAXN = 1000;
int n, left[MAXN], right[MAXN];

void link(int X, int Y) {
  right[X] = Y; left[Y] = X;
}

int main() {
  int m, X, Y;
  char type[9];
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) {
    left[i] = i-1; right[i] = i+1;
  }
  for(int i = 0; i < m; i++) {
    scanf("%s%d%d", &type, &X, &Y);
    link(left[X], right[X]);
    if(type[0] == 'A') {
      link(left[Y], X);
      link(X, Y);
    } else {
      link(X, right[Y]);
      link(Y, X);
    }
  }
  for(int X = right[0]; X != n+1; X = right[X])
    printf("%d ", X);
  printf("\n");
  return 0;
}
