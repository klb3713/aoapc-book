// UVa10794 The Deadly Olympic Returns
// 陈锋
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cfloat>
using namespace std;

typedef long long int64;

struct Point3 {
  int64 x, y, z;
  Point3(int64 x=0, int64 y=0, int64 z=0):x(x),y(y),z(z) { }
};

typedef Point3 Vector3;

Vector3 operator + (const Vector3& A, const Vector3& B) { return Vector3(A.x+B.x, A.y+B.y, A.z+B.z); }
Vector3 operator - (const Point3& A, const Point3& B) { return Vector3(A.x-B.x, A.y-B.y, A.z-B.z); }

int64 Dot(const Vector3& A, const Vector3& B) { return A.x*B.x + A.y*B.y + A.z*B.z; }
Vector3 Cross(Vector3 A, Vector3 B) { return Vector3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x); }

int64 readint64()
{
    int64 x;
    scanf("%lld", &x);
    return x;
}

Point3 read_point3() {
  Point3 p;
  p.x = readint64();
  p.y = readint64();
  p.z = readint64();
  return p;
}

/********************************************************************/

void solve(int64 c) {
    printf("Case %d: ", c);
    readint64();
    Point3 src1 = read_point3(), dest1 = read_point3();
    Point3 src2 = read_point3(), dest2 = read_point3();
    Vector3 v = (dest2 - src2) - (dest1 - src1); // 2相对于1的速度
    
    // 求点 src1 到射线 src2, v最短距离
    double ans;
    Vector3 ss = src1 - src2;
    if(Dot(v, v) == 0 || Dot(ss, v) <= 0)
        ans = sqrt(Dot(ss, ss));
    else
    {
        Vector3 c = Cross(v, ss);
        ans = Dot(c, c);
        ans /= Dot(v, v);
        ans = sqrt(ans);
    }
    
    printf("%.4f\n", ans);
}

int main()
{
    int64 T = readint64();
    for(int64 i = 1; i <= T; i++) solve(i);
    return 0;
}