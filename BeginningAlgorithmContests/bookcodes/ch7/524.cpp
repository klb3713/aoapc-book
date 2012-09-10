#include<cstdio>
#include<algorithm>
using namespace std;

int is_prime(int x) {
  for(int i = 2; i*i <= x; i++)
    if(x % i == 0) return 0;
  return 1;
}

int main() {
  int n, A[50], isp[50];
  scanf("%d", &n);
  for(int i = 2; i <= n*2; i++) isp[i] = is_prime(i);
  for(int i = 0; i < n; i++) A[i] = i+1;
  do {
    int ok = 1;
    for(int i = 0; i < n; i++) if(!isp[A[i]+A[(i+1)%n]]) {
      ok = 0;
      break;
    }
    if(ok) {
      for(int i = 0; i < n; i++) printf("%d ", A[i]);
      printf("\n");
    }
  }while(next_permutation(A+1, A+n));
  return 0;
}
