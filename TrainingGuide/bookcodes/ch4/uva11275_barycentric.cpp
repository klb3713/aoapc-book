// UVa11275 3D Triangles：用Barycentric坐标法判断点在三角形内
// Rujia Liu

#include<cstdio>
#include<cmath>
using namespace std;

struct Point3 {
  double x, y, z;
  Point3(double x=0, double y=0, double z=0):x(x),y(y),z(z) { }
};

typedef Point3 Vector3;

Vector3 operator + (const Vector3& A, const Vector3& B) { return Vector3(A.x+B.x, A.y+B.y, A.z+B.z); }
Vector3 operator - (const Point3& A, const Point3& B) { return Vector3(A.x-B.x, A.y-B.y, A.z-B.z); }
Vector3 operator * (const Vector3& A, double p) { return Vector3(A.x*p, A.y*p, A.z*p); }
Vector3 operator / (const Vector3& A, double p) { return Vector3(A.x/p, A.y/p, A.z/p); }

const double eps = 1e-8;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

double Dot(const Vector3& A, const Vector3& B) { return A.x*B.x + A.y*B.y + A.z*B.z; }
double Length(const Vector3& A) { return sqrt(Dot(A, A)); }
double Angle(const Vector3& A, const Vector3& B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
Vector3 Cross(const Vector3& A, const Vector3& B) { return Vector3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x); }
double Area2(const Point3& A, const Point3& B, const Point3& C) { return Length(Cross(B-A, C-A)); }

Point3 read_point3() {
  Point3 p;
  scanf("%lf%lf%lf", &p.x, &p.y, &p.z);
  return p;
}

// 点在三角形P0, P1, P2中
// http://www.blackpawn.com/texts/pointinpoly/default.html
bool PointInTri(const Point3& P, const Point3& P0, const Point3& P1, const Point3& P2) {
  Vector3 v0 = P2 - P0;
  Vector3 v1 = P1 - P0;
  Vector3 v2 = P - P0;

  // Compute dot products
  double dot00 = Dot(v0, v0);
  double dot01 = Dot(v0, v1);
  double dot02 = Dot(v0, v2);
  double dot11 = Dot(v1, v1);
  double dot12 = Dot(v1, v2);

  // Compute barycentric coordinates
  double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
  double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
  double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

  // Check if point is in triangle
  return (dcmp(u) >= 0) && (dcmp(v) >= 0) && (dcmp(u + v - 1) <= 0);
}

// 三角形P0P1P2是否和线段AB相交
bool TriSegIntersection(const Point3& P0, const Point3& P1, const Point3& P2, const Point3& A, const Point3& B, Point3& P) {
  Vector3 n = Cross(P1-P0, P2-P0);
  if(dcmp(Dot(n, B-A)) == 0) return false; // 线段A-B和平面P0P1P2平行或共面
  else { // 平面A和直线P1-P2有惟一交点
    double t = Dot(n, P0-A) / Dot(n, B-A);
    if(dcmp(t) < 0 || dcmp(t-1) > 0) return false; // 不在线段AB上
    P = A + (B-A)*t; // 交点
    return PointInTri(P, P0, P1, P2);
  }
}

bool TriTriIntersection(Point3* T1, Point3* T2) {
  Point3 P;
  for(int i = 0; i < 3; i++) {
    if(TriSegIntersection(T1[0], T1[1], T1[2], T2[i], T2[(i+1)%3], P)) return true;  
    if(TriSegIntersection(T2[0], T2[1], T2[2], T1[i], T1[(i+1)%3], P)) return true;  
  }
  return false;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    Point3 T1[3], T2[3];
    for(int i = 0; i < 3; i++) T1[i] = read_point3();
    for(int i = 0; i < 3; i++) T2[i] = read_point3();
    printf("%d\n", TriTriIntersection(T1, T2) ? 1 : 0);
  }
  return 0;
}
