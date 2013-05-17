// UVa10084 Hotter Colder
// 陈锋
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;

const double eps = 1e-8;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x = 0, double y = 0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }
double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
Vector Normal(const Vector& A) { double L = Length(A); return Vector(-A.y/L, A.x/L); }

// 调用前请确保两条直线P+tv和Q+tw有惟一交点。这当且仅当Cross(v,w)非零
Point GetLineIntersection(const Point& P, const Vector& v, const Point& Q, const Vector& w) { 
  Vector u = P-Q;
  double t = Cross(w, u) / Cross(v, w);
  return P+v*t;
}

bool OnSegment(const Point& p, const Point& a1, const Point& a2) {
  return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}

typedef vector<Point> Polygon;

double PolygonArea(const Polygon& p) {
  int n = p.size();
  double area = 0;
  for(int i = 1; i < n-1; i++)
    area += Cross(p[i]-p[0], p[i+1]-p[0]);
  return area/2;
}

Polygon CutPolygon(const Polygon& poly, const Point& A, const Point& B) {
  Polygon newpoly;
  int n = poly.size();
  for(int i = 0; i < n; i++) {
    const Point& C = poly[i], D = poly[(i+1)%n];
    
    Vector AB = B-A;
    if(dcmp(Cross(AB, C-A)) >= 0) newpoly.push_back(C);
    if(dcmp(Cross(AB, C-D)) != 0) {
      Point ip = GetLineIntersection(A, AB, C, D-C);
      if(OnSegment(ip, C, D)) newpoly.push_back(ip);
    }
  }
  
  return newpoly;
}

/********************************************************************/

int main()
{
    Polygon p;
    double x, y;
    char buf[16];
    Point prev;
    p.push_back(Point(0.0, 0.0));
    p.push_back(Point(10.0, 0.0));
    p.push_back(Point(10.0, 10.0));
    p.push_back(Point(0.0, 10.0));
    bool empty = false;
    
    while(true) {
        if(scanf("%lf%lf%s", &x, &y, buf) != 3) break;
        
        if(empty) { puts("0.00"); continue; }
        
        if(!strcmp(buf, "Same") || dcmp(PolygonArea(p) == 0)) { empty = true; puts("0.00"); continue; }
        
        Point cur(x, y);
        Point A((prev.x + x)*0.5, (prev.y+y)*0.5);
        
        Vector t = cur - prev;
        if(0 == strcmp(buf, "Colder"))
            p = CutPolygon(p, A, A + Vector(-t.y, t.x));
        else if(!strcmp(buf, "Hotter"))
            p = CutPolygon(p, A, A + Vector(t.y, -t.x));
        
        if(p.size() < 3) { empty = true; puts("0.00"); continue; }
        
        double area = PolygonArea(p);
        printf("%.2lf\n", fabs(area));
        
        prev = cur;
    }
    
    return 0;
}