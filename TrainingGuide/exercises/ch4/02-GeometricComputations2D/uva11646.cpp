// UVa11646 Athletics Track
// Rujia Liu
#include<cstdio>
#include<cmath>
int main() {
  int a, b, kase = 1;
  char c[10];
  while(scanf("%d%s%d", &a, &c, &b) == 3) {
    double R = sqrt(b*b+a*a)/2;
    double theta = 2*asin(b/(2*R));
    double p = theta*R + a;
    printf("Case %d: %.8f %.8f\n", kase++, 200*a/p, 200*b/p);
  }
  return 0;
}
