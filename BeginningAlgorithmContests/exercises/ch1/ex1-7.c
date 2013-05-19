/*
  œ∞Ã‚1-7 ¥Ú’€£®discount£©
  ¡ı»Íº—
*/

#include<stdio.h>
int main() {
  int n;
  scanf("%d", &n);
  double money = n * 95;
  if(money >= 300) money *= 0.85;
  printf("%.2lf\n", money);
  return 0;
}
