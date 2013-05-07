// UVa10439 Temple of Dune
// 陈锋
#include <cstring>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long int64;

#include <cstring>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) {}
};

typedef Point Vector;
const double eps = 1e-4;
double dcmp(double x) { if(fabs(x) < eps) return 0; return x < 0 ? -1 : 1; }

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }
double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
double Angle(const Vector& A, const Vector& B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }

Point GetLineIntersection(const Point& P, const Vector& v, const Point& Q, const Vector& w) {
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

int readint() {
    int x;
    scanf("%d", &x);
    return x;
}

/**********************************************************/

const double PI = acos(-1.0);
Point middle(const Vector& A, const Vector& B){ return Point((A.x + B.x)/2, (A.y + B.y)/2); }
Vector vertical(const Vector& A) { return Vector(-A.y, A.x); }
bool eq(double x, double y){ return dcmp(x - y) == 0; }
double angle(const Vector& A){ return atan2(A.y,A.x); }

void solve(){
    Point A = read_point(), B = read_point(), C = read_point();
    Point p = GetLineIntersection(middle(A, B), vertical(B - A), middle(B, C), vertical(B - C));
    double a = angle(A - p), b = angle(B - p), c = angle(C - p);
    
    for(int n = 3; n <= 200; n++) {
        double r = 2 * PI / n;        
        bool fA = false, fB = false, fC = false;
        for(int j = 1; j <= n; j++) {
            if(!fA) fA = eq(fabs(a-b), r*j);
            if(!fB) fB = eq(fabs(b-c), r*j);
            if(!fC) fC = eq(fabs(c-a), r*j);
            if(fA&&fB&&fC) { printf("%d\n", n); return; }
        }
    }
}

int main()
{
    int T = readint();
    for(int i = 0; i < T; i++)
        solve();
    return 0;
}
