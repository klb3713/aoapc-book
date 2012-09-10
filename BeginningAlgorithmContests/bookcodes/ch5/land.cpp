#include<stdio.h>
int main() {
  int n;
  scanf("%d", &n);
  int V = 0, E = 0;
  for(int i = 0; i <= n-2; i++)
    V += i*(n-2-i), E += i*(n-2-i)+1;
  V = V*n/4+n;
  E = E*n/2+n;
  printf("%d\n", E-V+1);
  return 0;
}
