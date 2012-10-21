// LA3263 That Nice Euler Circuit
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

bool OnSegment(const Point& p, const Point& a1, const Point& a2) {
  return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}

const int maxn = 300 + 10;
Point P[maxn], V[maxn*maxn];

int main() {
  int n, kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    for(int i = 0; i < n; i++) { scanf("%lf%lf", &P[i].x, &P[i].y); V[i] = P[i]; }
    n--;
    int c = n, e = n;
    for(int i = 0; i < n; i++)
      for(int j = i+1; j < n; j++)
        if(SegmentProperIntersection(P[i], P[i+1], P[j], P[j+1]))
          V[c++] = GetLineIntersection (P[i], P[i+1]-P[i], P[j], P[j+1]-P[j]);
    sort(V, V+c);
    c = unique(V, V+c) - V;
    for(int i = 0; i < c; i++)
      for(int j = 0; j < n; j++)
        if(OnSegment(V[i], P[j], P[j+1])) e++;
    printf("Case %d: There are %d pieces.\n", ++kase, e+2-c);
  }
  return 0;
}
