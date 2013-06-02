// UVa11836 Star War
// 陈锋
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cfloat>
using namespace std;

const double eps = 1e-6;
int dcmp(double x) { if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }

struct Point3 {
  double x, y, z;
  Point3(double x=0, double y=0, double z=0):x(x),y(y),z(z) { }
};

typedef Point3 Vector3;

Vector3 operator + (const Vector3& A, const Vector3& B) { return Vector3(A.x+B.x, A.y+B.y, A.z+B.z); }
Vector3 operator - (const Point3& A, const Point3& B) { return Vector3(A.x-B.x, A.y-B.y, A.z-B.z); }
Vector3 operator * (const Vector3& A, double p) { return Vector3(A.x*p, A.y*p, A.z*p); }
Vector3 operator / (const Vector3& A, double p) { return Vector3(A.x/p, A.y/p, A.z/p); }

bool operator == (const Point3& a, const Point3& b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0 && dcmp(a.z-b.z) == 0;
}

Point3 read_point3() {
  Point3 p;
  scanf("%lf%lf%lf", &p.x, &p.y, &p.z);
  return p;
}

double Dot(const Vector3& A, const Vector3& B) { return A.x*B.x + A.y*B.y + A.z*B.z; }
double Length(const Vector3& A) { return sqrt(Dot(A, A)); }
double Angle(const Vector3& A, const Vector3& B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
Vector3 Cross(const Vector3& A, const Vector3& B) { return Vector3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x); }
double Area2(const Point3& A, const Point3& B, const Point3& C) { return Length(Cross(B-A, C-A)); }
double Volume6(const Point3& A, const Point3& B, const Point3& C, const Point3& D) { return Dot(D-A, Cross(B-A, C-A)); }
Point3 Centroid(const Point3& A, const Point3& B, const Point3& C, const Point3& D) { return (A + B + C + D)/4.0; }

// 点p到平面p0-n的距离。n必须为单位向量
double DistanceToPlane(const Point3& p, const Point3& p0, const Vector3& n) {
  return fabs(Dot(p-p0, n)); // 如果不取绝对值，得到的是有向距离
}

// 点p在平面p0-n上的投影。n必须为单位向量
Point3 GetPlaneProjection(const Point3& p, const Point3& p0, const Vector3& n) {
  return p-n*Dot(p-p0, n);
}

// 点P在三角形P0, P1, P2中
bool PointInTri(Point3 P, Point3 P0, Point3 P1, Point3 P2) {
  double area1 = Area2(P, P0, P1);
  double area2 = Area2(P, P1, P2);
  double area3 = Area2(P, P2, P0);
  return dcmp(area1 + area2 + area3 - Area2(P0, P1, P2)) == 0;
}

// 点P到线段AB的距离
double DistanceToSegment(Point3 P, Point3 A, Point3 B) {
  if(A == B) return Length(P-A);
  Vector3 v1 = B - A, v2 = P - A, v3 = P - B;
  if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
  else if(dcmp(Dot(v1, v3)) > 0) return Length(v3);
  else return Length(Cross(v1, v2)) / Length(v1);
}

int readint()
{
    int x;
    scanf("%d", &x);
    return x;
}

// 求异面直线p1+su和p2+tv的公垂线对应的s。如果平行/重合，返回false
bool LineDistance3D(Point3 p1, Vector3 u, Point3 p2, Vector3 v, double& s) {
    double b = Dot(u,u)*Dot(v,v) - Dot(u,v)*Dot(u,v);
    if(dcmp(b) == 0) return false;
    double a = Dot(u,v)*Dot(v,p1-p2) - Dot(v,v)*Dot(u,p1-p2);
    s = a/b;
    return true;
}

/********************************************************************/

typedef pair<Point3, Point3> Segment3;

vector<Segment3> getEdges(const vector<Point3> p) {
    vector<Segment3> ans;
    int sz = p.size();
    for(int i = 0; i < sz; i++)
        for(int j = i + 1; j < sz; j++)
            ans.push_back(make_pair(p[i], p[j]));
    return ans;
}

// 点到三角形的最短距离
double dist2Tri(const Point3& p, const Point3& A, const Point3& B, const Point3& C) {
    double ans = DBL_MAX;    
    Vector3 n = Cross(B-A, C-A);
    n = n / Length(n);
    
    Point3 proj = GetPlaneProjection(p, A, n);
    if(PointInTri(proj, A, B, C))
    {
        ans = min(ans, DistanceToPlane(p, A, n));
    }
    else
    {
        ans = min(ans, DistanceToSegment(p, A, B));
        ans = min(ans, DistanceToSegment(p, B, C));
        ans = min(ans, DistanceToSegment(p, A, C));
        
        ans = min(ans, Length(p - A));
        ans = min(ans, Length(p - B));
        ans = min(ans, Length(p - C));
    }
    
    return ans;
}

double dist(const vector<Point3>& s1, const vector<Point3>& s2)
{
    // 先求点到三角形的距离
    double ans = DBL_MAX;
    vector<Point3> cs2;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            cs2.assign(s2.begin(), s2.end());
            cs2.erase(cs2.begin() + j);
            ans = min(ans, dist2Tri(s1[i], cs2[0], cs2[1], cs2[2]));
        }
    }
    
    // 再求所有的线段与线段之间的距离
    vector<Segment3> e1 = getEdges(s1), e2 = getEdges(s2);
    int sz = e1.size();
    for(int i = 0; i < sz; i++) {
        for(int j = 0; j < sz; j++) {
            double s, t;
            const Segment3& ei = e1[i], ej = e2[j];
            const Vector3& vi = ei.second - ei.first, vj = ej.second - ej.first;
            LineDistance3D(ei.first, vi, ej.first, vj, s);
            if(dcmp(s) >= 0 && dcmp(s - 1) <= 0)
            {
                LineDistance3D(ej.first, vj, ei.first, vi, t);
                if(dcmp(t) >= 0 && dcmp(t - 1) <= 0)
                {
                    Point3 ps = ei.first + vi * s, pt = ej.first + vj * t;
                    double d = Length(ps - pt);
                    ans = min(ans, d);
                }
            }
        }
    }
    
    return ans;
}

bool solve() {
    vector<Point3> s1, s2;
    
    for(int i = 0; i < 4; i++) s1.push_back(read_point3());
    for(int i = 0; i < 4; i++) s2.push_back(read_point3());
    
    printf("%.2lf\n", min(dist(s1, s2), dist(s2, s1)));
}

int main()
{
    int T = readint();
    for(int i = 0; i < T; i++) {
        solve();
    }

    return 0;
}