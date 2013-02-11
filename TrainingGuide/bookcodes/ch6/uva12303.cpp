// UVa12303 Composite Transformations
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<cassert>
using namespace std;

const double PI = acos(-1.0);

struct Point3 {
  double x, y, z;
  Point3(double x=0, double y=0, double z=0):x(x),y(y),z(z) { }
};

typedef Point3 Vector3;

Vector3 operator + (const Vector3& A, const Vector3& B) {
  return Vector3(A.x+B.x, A.y+B.y, A.z+B.z);
}

Vector3 operator - (const Point3& A, const Point3& B) {
  return Vector3(A.x-B.x, A.y-B.y, A.z-B.z);
}

Vector3 operator * (const Vector3& A, double p) {
  return Vector3(A.x*p, A.y*p, A.z*p);
}

Vector3 operator / (const Vector3& A, double p) {
  return Vector3(A.x/p, A.y/p, A.z/p);
}

double Dot(const Vector3& A, const Vector3& B) { return A.x*B.x + A.y*B.y + A.z*B.z; }
double Length(const Vector3& A) { return sqrt(Dot(A, A)); }
Vector3 Cross(const Vector3& A, const Vector3& B) { return Vector3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x); }

// 平面
struct Plane {
  double a, b, c, d;
  Plane() {}
  Plane(Point3* P) { // 用三点确定一个平面。调用者需保证三点不共线
    Vector3 V = Cross(P[1]-P[0], P[2]-P[0]);
    V = V / Length(V);
    a = V.x; b = V.y; c = V.z; d = -Dot(V, P[0]);
  }
  Point3 sample() const { // 随机采样
    double v1 = rand() / (double)RAND_MAX;
    double v2 = rand() / (double)RAND_MAX;
    if(a != 0) return Point3(-(d+v1*b+v2*c)/a, v1, v2);
    if(b != 0) return Point3(v1, -(d+v1*a+v2*c)/b, v2);
    if(c != 0) return Point3(v1, v2, -(d+v1*a+v2*b)/c);
    assert(0); // 不是一个平面
  }
};

// 4x4齐次变换矩阵
struct Matrix4x4 {
  double v[4][4];

  // 矩阵乘法
  inline Matrix4x4 operator * (const Matrix4x4 &rhs) const {
    Matrix4x4 ans;   
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            ans.v[i][j] = 0;
            for (int k = 0; k < 4; k++)
                ans.v[i][j] += v[i][k] * rhs.v[k][j];
        }
    return ans;
  }

  // 变换一个点，相当于右乘列向量(x, y, z, 1}
  inline Point3 transform(Point3 P) const {
    double p[4] = {P.x, P.y, P.z, 1}, ans[4] = {0};
    for(int i = 0; i < 4; i++)
      for(int k = 0; k < 4; k++)
        ans[i] += v[i][k] * p[k];
    return Point3(ans[0], ans[1], ans[2]); // ans[3]肯定是1
  }

  // 单位矩阵
  void loadIdentity() {
    memset(v, 0, sizeof(v));
    v[0][0] = v[1][1] = v[2][2] = v[3][3] = 1;
  }

  // 平移矩阵
  void loadTranslate(double a, double b, double c) {
    loadIdentity();
    v[0][3] = a; v[1][3] = b; v[2][3] = c;
  }

  // 缩放矩阵
  void loadScale(double a, double b, double c) {
    loadIdentity();
    v[0][0] = a; v[1][1] = b; v[2][2] = c;
  }

  // 绕固定轴旋转一定角度的矩阵
  void loadRotation(double a, double b, double c, double deg) {
    loadIdentity();
    double rad = deg / 180 * PI;
    double sine = sin(rad), cosine = cos(rad);
    Vector3 L(a, b, c);
    L = L / Length(L);
    v[0][0] = cosine + L.x * L.x * (1.0 - cosine);
    v[0][1] = L.x * L.y * (1 - cosine) - L.z * sine;
    v[0][2] = L.x * L.z * (1 - cosine) + L.y * sine;
    v[1][0] = L.y * L.x * (1 - cosine) + L.z * sine;
    v[1][1] = cosine + L.y * L.y * (1 - cosine);
    v[1][2] = L.y * L.z * (1 - cosine) - L.x * sine;
    v[2][0] = L.z * L.x * (1 - cosine) - L.y * sine;
    v[2][1] = L.z * L.y * (1 - cosine) + L.x * sine;
    v[2][2] = cosine + L.z * L.z * (1 - cosine);
  }
};

const int maxn = 50000 + 10;
const int maxp = 50000 + 10;
Point3 P[maxn];
Plane planes[maxp];

int main() {
  int n, m, T;
  scanf("%d%d%d", &n, &m, &T);
  for(int i = 0; i < n; i++)
    scanf("%lf%lf%lf", &P[i].x, &P[i].y, &P[i].z);
  for(int i = 0; i < m; i++)
    scanf("%lf%lf%lf%lf", &planes[i].a, &planes[i].b, &planes[i].c, &planes[i].d);

  // 点P将被变换为 M[T-1] * ... * M[2] * M[1] * M[0] * P
  // 根据结合律，先计算mat = (M[T-1] * ... * M[0])，则点P变换为mat * P
  Matrix4x4 mat;
  mat.loadIdentity();
  for(int i = 0; i < T; i++) {
    char op[100];
    double a, b, c, theta;
    scanf("%s%lf%lf%lf", op, &a, &b, &c);
    Matrix4x4 M;
    if(op[0] == 'T') M.loadTranslate(a, b, c);
    else if(op[0] == 'S') M.loadScale(a, b, c);
    else if(op[0] == 'R') { scanf("%lf", &theta); M.loadRotation(a, b, c, theta); }
    mat = M * mat;
  }

  // 变换点
  for(int i = 0; i < n; i++) {
    Point3 ans = mat.transform(P[i]);
    printf("%.2lf %.2lf %.2lf\n", ans.x, ans.y, ans.z);
  }
  // 变换平面
  for(int i = 0; i < m; i++) {
    Point3 A[3];
    for(int j = 0; j < 3; j++) A[j] = mat.transform(planes[i].sample());
    Plane pl(A);
    printf("%.2lf %.2lf %.2lf %.2lf\n", pl.a, pl.b, pl.c, pl.d);
  }
  return 0;
}
