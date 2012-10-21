// UVa11796 Dog Distance
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const double eps = 1e-8;
int dcmp(double x) { if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }

const double PI = acos(-1.0);
double torad(double deg) { return deg/180 * PI; }

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }
Vector operator / (const Vector& A, double p) { return Vector(A.x/p, A.y/p); }

bool operator < (const Point& a, const Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator == (const Point& a, const Point &b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

Point read_point() {
  double x, y;
  scanf("%lf%lf", &x, &y);
  return Point(x, y);
};

double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }

double DistanceToSegment(const Point& P, const Point& A, const Point& B) {
  if(A == B) return Length(P-A);
  Vector v1 = B - A, v2 = P - A, v3 = P - B;
  if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
  else if(dcmp(Dot(v1, v3)) > 0) return Length(v3);
  else return fabs(Cross(v1, v2)) / Length(v1);
}

const int maxn = 60;
int T, A, B;
Point P[maxn], Q[maxn];
double Min, Max;

void update(Point P, Point A, Point B) {
  Min = min(Min, DistanceToSegment(P, A, B));
  Max = max(Max, Length(P-A));
  Max = max(Max, Length(P-B));
}

int main() {
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%d%d", &A, &B);
    for(int i = 0; i < A; i++) P[i] = read_point();
    for(int i = 0; i < B; i++) Q[i] = read_point();

    double LenA = 0, LenB = 0;
    for(int i = 0; i < A-1; i++) LenA += Length(P[i+1]-P[i]);
    for(int i = 0; i < B-1; i++) LenB += Length(Q[i+1]-Q[i]);

    int Sa = 0, Sb = 0;
    Point Pa = P[0], Pb = Q[0];
    Min = 1e9, Max = -1e9;
    while(Sa < A-1 && Sb < B-1) {
      double La = Length(P[Sa+1] - Pa); // 甲到下一拐点的距离
      double Lb = Length(Q[Sb+1] - Pb); // 乙到下一拐点的距离
      double T = min(La/LenA, Lb/LenB); // 取合适的单位，可以让甲和乙的速度分别是LenA和LenB
      Vector Va = (P[Sa+1] - Pa)/La*T*LenA; // 甲的位移向量
      Vector Vb = (Q[Sb+1] - Pb)/Lb*T*LenB; // 乙的位移向量
      update(Pa, Pb, Pb+Vb-Va); // 求解“简化版”，更新最小最大距离
      Pa = Pa + Va;
      Pb = Pb + Vb;
      if(Pa == P[Sa+1]) Sa++;
      if(Pb == Q[Sb+1]) Sb++;
    }
    printf("Case %d: %.0lf\n", kase, Max-Min);
  }
  return 0;
}
