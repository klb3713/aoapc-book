/*
  œ∞Ã‚1-5 æ‡¿Î£®distance£©
  ¡ı»Íº—
*/

#include<stdio.h>
#include<math.h>
int main() {
  double x1, y1, x2, y2;
  scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
  printf("%.3lf\n", sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
  return 0;
}
