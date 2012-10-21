// LA4127 The Sky is the Limit
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const double eps = 1e-10;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }

bool operator < (const Point& a, const Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator == (const Point& a, const Point &b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }

Point GetLineIntersection(const Point& P, const Vector& v, const Point& Q, const Vector& w) { 
  Vector u = P-Q;
  double t = Cross(w, u) / Cross(v, w);
  return P+v*t;
}

bool SegmentProperIntersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
  double c1 = Cross(a2-a1,b1-a1), c2 = Cross(a2-a1,b2-a1),
  c3 = Cross(b2-b1,a1-b1), c4=Cross(b2-b1,a2-b1);
  return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

const int maxn = 100 + 10;
Point P[maxn], L[maxn][2][2];
double x[maxn*maxn];

int main() {
  int n, kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    int c = 0;
    for(int i = 0; i < n; i++) {
      double X, H, B;
      scanf("%lf%lf%lf", &X, &H, &B);
      L[i][0][0] = Point(X-B*0.5, 0);
      L[i][0][1] = L[i][1][0] = Point(X, H);
      L[i][1][1] = Point(X+B*0.5, 0);
      x[c++] = X-B*0.5;
      x[c++] = X;
      x[c++] = X+B*0.5;
    }
    for(int i = 0; i < n; i++) for(int a = 0; a < 2; a++)
      for(int j = i+1; j < n; j++) for(int b = 0; b < 2; b++) {
        Point P1 = L[i][a][0], P2 = L[i][a][1], P3 = L[j][b][0], P4 = L[j][b][1];
        if(SegmentProperIntersection(P1, P2, P3, P4))
          x[c++] = GetLineIntersection(P1, P2-P1, P3, P4-P3).x;
      }

    // 根据所有交点离散化
    sort(x, x+c);
    c = unique(x, x+c) - x;

    double ans = 0;
    Point lastp;
    for(int k = 0; k < c; k++) {
      // 计算直线x=x[k]和山相交的最高点
      Point P(x[k], 0);
      Vector V(0, 1);
      double maxy = -1;
      for(int i = 0; i < n; i++) for(int a = 0; a < 2; a++) {
        Point P1 = L[i][a][0], P2 = L[i][a][1];
        Point intersection = GetLineIntersection(P, V, P1, P2-P1);
        if(dcmp(intersection.x-P1.x) >= 0 && dcmp(intersection.x-P2.x) <= 0)
          maxy = max(maxy, intersection.y);
      }
      Point newp(x[k], maxy);
      if(k > 0 && (dcmp(lastp.y) > 0 || dcmp(maxy) > 0)) ans += Length(newp - lastp);
      lastp = newp;
    }

    printf("Case %d: %.0lf\n\n", ++kase, ans);
  }
  return 0;
}
