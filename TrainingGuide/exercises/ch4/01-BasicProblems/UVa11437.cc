// UVa11437 Triangle Fun
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
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }
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

Point getF(const Point& A, const Point& B)
{
    return A + (B - A) / 3;
}

// 线段 [A, A0]和[B, B0]的交点
Point intersect(const Point& A, const Point& A0, const Point& B, const Point& B0)
{
    return GetLineIntersection(A, A0-A, B, B0-B);
}

void solve()
{
    Point A = read_point();
    Point B = read_point();
    Point C = read_point();
    
    Point F = getF(A, B);
    Point D = getF(B, C);
    Point E = getF(C, A);   
    
    // P, AD cross BE 
    Point P = intersect(A, D, B, E);
    
    // Q, BE cross CF
    Point Q = intersect(B, E, C, F);
    
    // R, AD cross CF
    Point R = intersect(A, D, C, F);
    
    double a = abs(Cross(P - Q, P - R)) / 2;
    printf("%d\n", (int)floor(a + 0.5));
}

int main()
{
    int N = readint();
    for(int i = 0; i < N; i++)
        solve();
    
    return 0;
}
