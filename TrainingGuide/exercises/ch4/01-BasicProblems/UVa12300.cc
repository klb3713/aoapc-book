// UVa12300 Smallest Regular Polygon
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
double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }

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
Point A, B;
int n;

void solve()
{
    double r = Length(B - A) / 2;
    if(n % 2){
        double a = PI * (n/2) / n;
        r /= sin(a);
    }
        
    double d = PI / n;
    double ans = r * r * cos(d) * sin(d) * n;
    printf("%.6f\n",ans);
}

int main()
{
    while(true){
        A = read_point(), B = read_point();
        n = readint();
        if(!n) break;
        solve();
    }
    return 0;
}
