/*
  Ï°Ìâ1-8 ¾ø¶ÔÖµ£¨abs£©
  ÁõÈê¼Ñ
*/

#include<stdio.h>
int main() {
  double x;
  scanf("%lf", &x);
  if(x < 0) x = -x;
  printf("%.2lf\n", x);
  return 0;
}
