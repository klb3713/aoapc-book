// UVa694 The Collatz Sequence
// Rujia Liu
#include<cstdio>
int solve(int a, int limit) {
  int cnt = 1;
  while(a != 1) {
    if(a % 2 == 0) a /= 2;
    else {
      long long tmp = (long long)a * 3 + 1;
      if(tmp > limit) break;
      a = tmp;
    }
    cnt++;
  }
  return cnt;
}

int main() {
  int a, limit, kase = 0;
  while(scanf("%d%d", &a, &limit) == 2 && a > 0) {
    printf("Case %d: A = %d, limit = %d, number of terms = %d\n", ++kase, a, limit, solve(a, limit));
  }
  return 0;
}