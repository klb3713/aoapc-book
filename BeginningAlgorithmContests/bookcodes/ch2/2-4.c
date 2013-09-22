#include<stdio.h>
int main(){
  int n, count = 0;
  scanf("%d", &n);
  while(n > 1) {
    if(n % 2 == 1) n = n*3+1;
    else n /= 2;
    count++;
  }
  printf("%d\n", count);
  return 0;
}
