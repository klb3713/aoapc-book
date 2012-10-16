// UVa10341 Solve It
// Rujia Liu
#include<stdio.h>
#include<math.h>
#define F(x) (p*exp(-x)+q*sin(x)+r*cos(x)+s*tan(x)+t*(x)*(x)+u)
const double eps = 1e-14;
int main() {
  int p, r, q, s, t, u;
  while(scanf("%d%d%d%d%d%d", &p, &q, &r, &s, &t, &u) == 6) {
    double f0 = F(0), f1 = F(1);
    if(f1 > eps || f0 < -eps) printf("No solution\n");
    else {
      double x = 0, y = 1, m;
      for(int i = 0; i < 100; i++) {
        m = x + (y-x)/2;
        if(F(m) < 0) y = m; else x = m;
      }
      printf("%.4lf\n", m);
    }
  }
  return 0;
}
