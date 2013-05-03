// UVa11817 Tunnelling the Earth
// Rujia Liu
#include<cstdio>
#include<cmath>
using namespace std;
const double R = 6371009;

double torad(double deg) {
  return deg/180 * M_PI;
}

void get_coord(double lat, double lng, double& x, double& y, double& z) {
  lat = torad(lat);
  lng = torad(lng);
  x = R*cos(lat)*cos(lng);
  y = R*cos(lat)*sin(lng);
  z = R*sin(lat);
}

double sqr(double x) { return x*x; }

double dist(double x1, double y1, double z1, double x2, double y2, double z2) {
  return sqrt(sqr(x1-x2)+sqr(y1-y2)+sqr(z1-z2));
}

int main() {
  int T;
  double lat1, lng1, lat2, lng2;
  double x1, y1, z1, x2, y2, z2;
  scanf("%d", &T);
  while(T--) {
    scanf("%lf%lf%lf%lf", &lat1, &lng1, &lat2, &lng2);
    get_coord(lat1, lng1, x1, y1, z1);
    get_coord(lat2, lng2, x2, y2, z2);
    double d = dist(x1, y1, z1, x2, y2, z2);
    double d2 = 2*asin(d/(2*R))*R;
    printf("%.0lf\n", d2-d);
  }
  return 0;
}
