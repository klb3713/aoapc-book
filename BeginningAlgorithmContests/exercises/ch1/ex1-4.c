/*
  œ∞Ã‚1-4 ’˝œ“∫Õ”‡œ“£®sincos£©
  ¡ı»Íº—
*/

#include<stdio.h>
#include<math.h>
const double PI = 2 * acos(0);
int main() {
  int n;
  scanf("%d", &n);
  printf("%.3lf %.3lf\n", sin(n/180.0*PI), cos(n/180.0*PI));
  return 0;
}
