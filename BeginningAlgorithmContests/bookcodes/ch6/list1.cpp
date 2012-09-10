#include<stdio.h>
const int MAXN = 1000;
int n, A[MAXN];

int find(int X) {
  for(int i = 1; i <= n; i++)
    if(A[i] == X) return i;
  return 0;
}

void shift_circular_left(int a, int b) {
  int t = A[a];
  for(int i = a; i < b; i++) A[i] = A[i+1];
  A[b] = t;
}

void shift_circular_right(int a, int b) {
  int t = A[b];
  for(int i = b; i > a; i--) A[i] = A[i-1];
  A[a] = t;
}

int main() {
  int m, X, Y, p, q;
  char type[9];
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++)
    A[i] = i;
  for(int i = 0; i < m; i++) {
    scanf("%s%d%d", &type, &X, &Y);
    p = find(X);
    q = find(Y);
    if(type[0] == 'A') {
      if(q > p) shift_circular_left(p, q-1);
      else shift_circular_right(q, p);
    } else {
      if(q > p) shift_circular_left(p, q);
      else shift_circular_right(q+1, p);
    }
  }
  for(int i = 1; i <= n; i++)
    printf("%d ", A[i]);
  printf("\n");
  return 0;
}
