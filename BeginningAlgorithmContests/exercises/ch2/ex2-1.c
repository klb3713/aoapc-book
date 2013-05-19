/*
  Ï°Ìâ2-1. Î»Êı£¨digit£©
  ÁõÈê¼Ñ
*/

#include<stdio.h>
int main() {
  int n, d = 0;
  scanf("%d", &n);
  do {
    n /= 10;
    d++;
  } while(n > 0);
  printf("%d\n", d);
  return 0;
}
