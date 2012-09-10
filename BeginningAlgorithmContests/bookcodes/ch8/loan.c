#include<stdio.h>
int main() {
  double a, c, x = 0, y = 100;
  int i, b;
  scanf("%lf%d%lf", &a, &b, &c);
  while(y-x > 1e-5) {
    double m = x+(y-x)/2;
    double f = a;
    for(i = 0; i < b; i++) f += f*m/100.0-c;
    if(f < 0) x=m; else y=m;
  }
  printf("%.3lf%%\n", x);
  return 0;
}
