/*
  Ï°Ìâ2-3. º«ĞÅµã±ø£¨hanxin£©
  ÁõÈê¼Ñ
*/

#include<stdio.h>
int main() {
  int i, a, b, c, n = -1;
  scanf("%d%d%d", &a, &b, &c);
  for(i = 10; i <= 100; i++)
    if(i % 3 == a && i % 5 == b && i % 7 == c) {
      n = i;
      break;
    }
  if(n < 0) printf("No answer\n");
  else printf("%d\n", n);
  return 0;
}
