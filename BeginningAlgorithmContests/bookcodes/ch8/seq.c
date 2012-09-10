#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
int A[100000], S[100000];

int cubic(int* A, int n) {
  int i, j, k, tot, best;
  tot = 0;
  best = A[1];
  for(i = 1; i <= n; i++)
    for(j = i; j <= n; j++) {
      int sum = 0;
      for(k = i; k <= j; k++) {
        sum += A[k];
        tot++;
      }
      if(sum > best) best = sum;
    }
  printf("tot = %d\n", tot);
  return best;
}

int square(int* A, int* S, int n) {
  int i, j, tot, best;
  tot = 0;
  best = A[1];
  S[0] = 0;
  for(i = 1; i <= n; i++)
    S[i] = S[i-1] + A[i];
  for(i = 1; i <= n; i++)
    for(j = i; j <= n; j++) {
      if(S[j] - S[i-1] >= best)
        best = S[j] - S[i-1];
      tot++;
    }
  printf("tot = %d\n", tot);
  return best;
}

int nlogn(int* A, int x, int y, int* tot) {
  int i, m, v, L, R, max;
  if(y - x == 1) return A[x];

  m = x + (y-x)/2;
  max = nlogn(A, x, m, tot);
  v = nlogn(A, m, y, tot);
  if(v > max) max = v;

  v = 0; L = A[m-1];
  for(i = m-1; i >= x; i--) {
    v += A[i];
    if(v > L) L = v;
    (*tot)++;
  }
  v = 0; R = A[m];
  for(i = m; i < y; i++) {
    v += A[i];
    if(v > R) R = v;
    (*tot)++;
  }
  if(L + R > max) max = L + R;
  return max;
}

int main() {
  int x1, x2, x3, tot = 0, i, n;
  scanf("%d", &n);
  srand(time(NULL));
  for(i = 1; i <= n; i++)
    A[i] = rand();
  x1 = cubic(A, n);
  x2 = square(A, S, n);
  x3 = nlogn(A, 1, n+1, &tot);
  printf("tot = %d\n", tot);
  printf("%d %d %d\n", x1, x2, x3);
  assert(x1 == x2 && x1 == x3);
  return 0;
}
