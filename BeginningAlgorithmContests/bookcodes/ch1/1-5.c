#include<stdio.h>
#include<math.h>
int main(){
  const double pi = 4.0 * atan(1.0);
  double r, h, s1, s2, s;
  scanf("%lf%lf", &r, &h);
  s1 = pi * r * r;
  s2 = 2 * pi * r * h;
  s = s1 * 2.0 + s2;
  printf("Area = %.3lf\n", s);
  return 0;
}
