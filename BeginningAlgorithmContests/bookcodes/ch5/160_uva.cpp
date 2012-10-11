#include<stdio.h>
#include<string.h>

int is_prime(int n) {
  for(int i = 2; i*i <= n; i++)
    if(n % i == 0) return 0;
  return 1;
}

int prime[100], count = 0;
int main() {
  int n, p[100];
  for(int i = 2; i <= 100; i++)
    if(is_prime(i)) prime[count++] = i;

  while(scanf("%d", &n) == 1 && n > 0) {
    printf("%3d! =", n);
    memset(p, 0, sizeof(p));
    int maxp = 0;
    for(int i = 1; i <= n; i++) {
      int m = i;
      for(int j = 0; j < count; j++)
        while(m % prime[j] == 0) {
          m /= prime[j];
          p[j]++;
          if(j > maxp) maxp = j;
        }
    }
    int count = 0;
    for(int i = 0; i <= maxp; i++) {
      if(count > 0 && count % 15 == 0) printf("\n      ");
      printf("%3d", p[i]);
      ++count;
    }
    printf("\n");
  }
  return 0;
}
