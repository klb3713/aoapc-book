// UVa11178 Morley's Theorem
// Rujia Liu
#include<cstdio>
#include<cmath>

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }
double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
double Angle(const Vector& A, const Vector& B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }

Point GetLineIntersection(const Point& P, const Point& v, const Point& Q, const Point& w) {
  Vector u = P-Q;
  double t = Cross(w, u) / Cross(v, w);
  return P+v*t;
}

Vector Rotate(const Vector& A, double rad) {
  return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}

Point read_point() {
  double x, y;
  scanf("%lf%lf", &x, &y);
  return Point(x,y);
}

Point getD(Point A, Point B, Point C) {
  Vector v1 = C-B;
  double a1 = Angle(A-B, v1);
  v1 = Rotate(v1, a1/3);

  Vector v2 = B-C;
  double a2 = Angle(A-C, v2);
  v2 = Rotate(v2, -a2/3);

  return GetLineIntersection(B, v1, C, v2);
}

int main() {
  int T;
  Point A, B, C, D, E, F;
  scanf("%d", &T);
  while(T--) {
    A = read_point();
    B = read_point();
    C = read_point();
    D = getD(A, B, C);
    E = getD(B, C, A);
    F = getD(C, A, B);
    printf("%.6lf %.6lf %.6lf %.6lf %.6lf %.6lf\n", D.x, D.y, E.x, E.y, F.x, F.y);
  }
  return 0;
}
