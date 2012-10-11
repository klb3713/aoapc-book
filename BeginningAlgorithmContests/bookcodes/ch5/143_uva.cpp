#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int FACTOR = 100;

bool left_or_on(int x1, int y1, int x2, int y2) {
  return x1*y2 - x2*y1 >= 0;
}

int main() {
  double x1_, y1_, x2_, y2_, x3_, y3_;
  while(scanf("%lf%lf%lf%lf%lf%lf", &x1_, &y1_, &x2_, &y2_, &x3_, &y3_) == 6) {
    int x1 = (int)(x1_*FACTOR+0.5);
    int y1 = (int)(y1_*FACTOR+0.5);
    int x2 = (int)(x2_*FACTOR+0.5);
    int y2 = (int)(y2_*FACTOR+0.5);
    int x3 = (int)(x3_*FACTOR+0.5);
    int y3 = (int)(y3_*FACTOR+0.5);
    if(x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0 && x3 == 0 && y3 == 0) break;

    int minx = int(min(min(x1, x2), x3));
    int maxx = int(max(max(x1, x2), x3));
    int miny = int(min(min(y1, y2), y3));
    int maxy = int(max(max(y1, y2), y3));
    if(minx % FACTOR != 0) minx = (minx / FACTOR + 1) * FACTOR;
    if(maxx % FACTOR != 0) maxx = maxx / FACTOR * FACTOR;
    if(miny % FACTOR != 0) miny = (miny / FACTOR + 1) * FACTOR;
    if(maxy % FACTOR != 0) maxy = maxy / FACTOR * FACTOR;

    if(minx < FACTOR) minx = FACTOR;
    if(maxx > 99 * FACTOR) maxx = 99 * FACTOR;
    if(miny < FACTOR) miny = FACTOR;
    if(maxy > 99 * FACTOR) maxy = 99 * FACTOR;

    if(!left_or_on(x2-x1, y2-y1, x3-x1, y3-y1)) { swap(x2, x3); swap(y2, y3); }

    int ans = 0;
    for(int x = minx; x <= maxx; x += FACTOR)
      for(int y = miny; y <= maxy; y += FACTOR) {
        if(!left_or_on(x2-x1, y2-y1, x-x1, y-y1)) continue;
        if(!left_or_on(x3-x2, y3-y2, x-x2, y-y2)) continue;
        if(!left_or_on(x1-x3, y1-y3, x-x3, y-y3)) continue;
        ans++;
      }
    printf("%4d\n", ans);
  }
  return 0;
}
