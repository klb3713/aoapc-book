// UVa12301 An Angular Puzzle
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long int64;

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

Point GetLineIntersection(const Point& P, const Vector& v, const Vector& Q, const Point& w) {
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

void print_point(const Point& p) {
    printf("[%g, %g]", p.x, p.y);
}

int readint()
{
    int x;
    scanf("%d", &x);
    return x;
}

/**********************************************************/

const double PI = acos(-1.0);
Vector rotate(const Vector& A, double d)
{  
    return Rotate(A, d/180*PI);
}

int a, b, c, d, e;

void solve()
{
    if(a + b + c + d + e != 180 ) { puts("Impossible"); return; }
    Point A(0, 0), B(10, 0);
    Vector AB = B - A;
    Vector AC = rotate(AB, b + c), BC = rotate(AB, 180 - d - e),
        AE = rotate(AB, c), BD = rotate(AB, 180 - e);
    Point D = GetLineIntersection(A, AC, B, BD), E = GetLineIntersection(B, BC, A, AE);
    double r = Angle(D - E, A - E);
    printf("%.2f\n", r / PI * 180);
}

int main()
{
    while(true){
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
        if(!a) break;
        solve();
    }
    return 0;
}
