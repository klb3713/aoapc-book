// UVa10795 A Different Task
// Rujia Liu
#include<cstdio>

long long f(int* P, int i, int final) {
  if(i == 0) return 0;
  if(P[i] == final) return f(P, i-1, final);
  return f(P, i-1, 6-P[i]-final) + (1LL << (i-1));
}

const int maxn = 60 + 10;
int n, start[maxn], finish[maxn];

int main() {
  int kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    for(int i = 1; i <= n; i++) scanf("%d", &start[i]);
    for(int i = 1; i <= n; i++) scanf("%d", &finish[i]);
    int k = n;
    while(k >= 1 && start[k] == finish[k]) k--;

    long long ans = 0;
    if(k >= 1) {
      int other = 6-start[k]-finish[k];
      ans = f(start, k-1, other) + f(finish, k-1, other) + 1;
    }
    printf("Case %d: %lld\n", ++kase, ans);
  }
  return 0;
}
