#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const double eps = 1e-14;

inline double eval(double x, int p, int q, int r, int s, int t, int u)
{
 return p * exp(-x) + q * sin(x) + r * cos(x) + s * tan(x) + t * x * x + u;
}

int main()
{
 int p, q, r, s, t, u;
 while(scanf("%d%d%d%d%d%d", &p, &q, &r, &s, &t, &u) == 6)
 {
  double m, x, y, fx, fy;
  
  x = 0, y = 1;
  fx = eval(x,p,q,r,s,t,u);
  fy = eval(y,p,q,r,s,t,u);
  
  if(fx < -eps || fy > eps)
  {
   puts("No solution");
   continue;
  }
  
  while(y - x > eps)
  {
   double fm;
   m = x + (y-x)/2;
   fm = eval(m,p,q,r,s,t,u);
   
   if(fm < 0) y = m;
   else x = m;
  }
  
  printf("%.4lf\n", m);
 }
 return 0;
}
