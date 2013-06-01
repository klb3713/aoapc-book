// UVa1360(LA3500) Model Rocket Height 
// 陈锋
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cfloat>
using namespace std;

const double eps = 1e-8;
int dcmp(double x) { if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }

double read_double()
{
    double x;
    scanf("%lf", &x);
    return x;
}

const double PI = acos(-1.0);

struct Point3 {
  double x, y, z;
  Point3(double x=0, double y=0, double z=0):x(x),y(y),z(z) { }   
};

typedef Point3 Vector3;

Vector3 operator + (const Vector3& A, const Vector3& B) { return Vector3(A.x+B.x, A.y+B.y, A.z+B.z); }
Vector3 operator - (const Point3& A, const Point3& B) { return Vector3(A.x-B.x, A.y-B.y, A.z-B.z); }
double Dot(const Vector3& A, const Vector3& B) { return A.x*B.x + A.y*B.y + A.z*B.z; }
double Length(const Vector3& A) { return sqrt(Dot(A, A)); }
Vector3 Cross(Vector3 A, Vector3 B) { return Vector3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x); }
Vector3 operator * (Vector3 A, double p) { return Vector3(A.x*p, A.y*p, A.z*p); }


double d2r(double d) {
    return d * PI / 180.0;
}

double tand(double d) {
    double r = d2r(d);
    return tan(r);
}

// 求异面直线p1+su和p2+tv的公垂线对应的s。如果平行/重合，返回false
bool LineDistance3D(Point3 p1, Vector3 u, Point3 p2, Vector3 v, double& s) {
    double b = Dot(u,u)*Dot(v,v) - Dot(u,v)*Dot(u,v);
    if(dcmp(b) == 0) return false;
    double a = Dot(u,v)*Dot(v,p1-p2) - Dot(v,v)*Dot(u,p1-p2);
    s = a/b;
    return true;
}

int main()
{
    int N; 
    scanf("%d", &N);
    const double hA = read_double(), hB = read_double();
    const Point3 A(50, 50, 0), B(-50, 50, 0), C(50, 50, hA), D(-50, 50, hB);
    
    for(int i = 1; i <= N; i++) {
        double a, b, c, d;
        scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
        
        Point3 E(50.0-50.0/tand(c), 0, 0), F(-50.0-50.0/tand(d), 0, 0);
        Point3 G(E.x, 0, hA + Length(A - E)*tand(a)), H(F.x, 0, hB + Length(B - F)*tand(b));        
        
        double s = 0, t = 0;
        Vector3 CG = G - C, DH = H - D;
        LineDistance3D(C, CG, D, DH, s);
        LineDistance3D(D, DH, C, CG, t);
        
        Point3 r2 = (C + CG*s + D + DH*t) * .5;
        double ans = r2.z;
        printf("%d: %.lf\n", i, floor(ans + .5));
    }
    return 0;
}