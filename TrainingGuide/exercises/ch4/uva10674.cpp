// UVa10674 Tangents
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

const double PI = acos(-1);

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) {
  return Vector(A.x+B.x, A.y+B.y);
}

Vector operator - (Point A, Point B) {
  return Vector(A.x-B.x, A.y-B.y);
}

Vector operator * (Vector A, double p) {
  return Vector(A.x*p, A.y*p);
}

Vector operator / (Vector A, double p) {
  return Vector(A.x/p, A.y/p);
}

const double eps = 1e-8;
double dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

bool operator < (const Point& a, const Point& b) {
  return dcmp(a.x-b.x) < 0 || (dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) < 0);
}

bool operator == (const Point& a, const Point &b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }

// 本题相关

struct Circle {
  int x, y, r;
  Point getPoint(double a) {
    return Point(x+r*cos(a), y+r*sin(a));
  }
};

int getTangents(Circle A, Circle B, Point* a, Point* b) {
  int cnt = 0;
  if(A.r < B.r) { swap(A, B); swap(a, b); }
  int d2 = (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
  int rdiff = A.r-B.r;
  int rsum = A.r+B.r;
  if(d2 < rdiff*rdiff) return 0;

  double base = atan2(B.y-A.y, B.x-A.x);
  if(d2 == 0 && A.r == B.r) return -1; // 无限多条切线
  if(d2 == rdiff*rdiff) { // 内切，1条切线
    a[cnt] = A.getPoint(base); b[cnt] = B.getPoint(base); cnt++;
    return 1;
  }
  // 有外共切线
  double ang = acos((A.r-B.r) / sqrt(d2));
  a[cnt] = A.getPoint(base+ang); b[cnt] = B.getPoint(base+ang); cnt++;
  a[cnt] = A.getPoint(base-ang); b[cnt] = B.getPoint(base-ang); cnt++;
  if(d2 == rsum*rsum) { // 一条内共切线
    a[cnt] = A.getPoint(base); b[cnt] = B.getPoint(PI+base); cnt++;
  }
  else if(d2 > rsum*rsum) { // 两条内共切线
    double ang = acos((A.r+B.r) / sqrt(d2));
    a[cnt] = A.getPoint(base+ang); b[cnt] = B.getPoint(PI+base+ang); cnt++;
    a[cnt] = A.getPoint(base-ang); b[cnt] = B.getPoint(PI+base-ang); cnt++;
  }
  return cnt;
}

int main() {
  int x1, y1, r1, x2, y2, r2;
  while(scanf("%d%d%d%d%d%d", &x1, &y1, &r1, &x2, &y2, &r2) == 6 && r1) {
    Point a[4], b[4];
    int n = getTangents((Circle){x1, y1, r1}, (Circle){x2, y2, r2}, a, b);
    printf("%d\n", n);
    if(n > 0) {
      int p[4] = {0, 1, 2, 3};
      for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
          if(a[p[j]] < a[p[i]] || (a[p[i]] == a[p[j]] && b[p[j]] < b[p[i]])) swap(p[i], p[j]);
      for(int i = 0; i < n; i++)
        printf("%.5lf %.5lf %.5lf %.5lf %.5lf\n", a[p[i]].x, a[p[i]].y, b[p[i]].x, b[p[i]].y, Length(a[p[i]]-b[p[i]]));
    }
  }
  return 0;
}
