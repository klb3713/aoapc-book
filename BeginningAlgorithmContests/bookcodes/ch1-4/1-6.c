#include<stdio.h>
int main(){
  int n;
  scanf("%d", &n);
  printf("%d%d%d\n", n%10, n/10%10, n/100);
  return 0;
}
