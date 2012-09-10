#include<stdio.h>
#include<math.h>
double area(double x1, double y1, double x2, double y2, double x3, double y3) {
  return fabs(x1*y3+x2*y1+x3*y2-x2*y3-x3*y1-x1*y2);
}

int main() {
  double x1, y1, x2, y2, x3, y3;
  while(scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3) == 6) {
    int ans = 0;
    for(int x = 1; x <= 99; x++)
      for(int y = 1; y <= 99; y++)
        if(fabs(area(x1,y1,x2,y2,x,y)+area(x2,y2,x3,y3,x,y)+area(x3,y3,x1,y1,x,y)-area(x1,y1,x2,y2,x3,y3)) < 1e-8) ans++;
    printf("%d\n", ans);
  }
  return 0;
}
