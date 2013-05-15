// LA2453(UVa1033) Wall
// 陈锋
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;

const double PI = acos(-1);

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }
bool operator < (const Point& p1, const Point& p2) { return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y); }
bool operator == (const Point& a, const Point &b) { return a.x == b.x && a.y == b.y; }


double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
double Angle(const Vector& A, const Vector& B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }

Point read_point() {
  double x, y;
  scanf("%lf%lf", &x, &y);
  return Point(x,y);
}

// 点集凸包
// 如果不希望在凸包的边上有输入点，把两个 <= 改成 <
// 注意：输入点集会被修改
vector<Point> ConvexHull(vector<Point>& p) {
  // 预处理，删除重复点
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());

  int n = p.size();
  int m = 0;
  vector<Point> ch(n+1);
  for(int i = 0; i < n; i++) {
    while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) < 0) m--;
    ch[m++] = p[i];
  }
  int k = m;
  for(int i = n-2; i >= 0; i--) {
    while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) < 0) m--;
    ch[m++] = p[i];
  }
  if(n > 1) m--;
  ch.resize(m);
  return ch;
}

int readint()
{
    int x;
    scanf("%d", &x);
    return x;
}

/********************************************************************/
void solve(int t){
    if(t) puts("");
    
    int N = readint();
    double L = readint();
    vector<Point> v;
    for(int i = 0; i < N; i++) v.push_back(read_point());
    vector<Point> ch = ConvexHull(v);
    
    double ans = 0;
    int sz = ch.size();
    for(int i = 0; i < sz; i++)
        ans += Length(ch[(i+1)%sz] - ch[i]);
    ans += 2 * PI * L;
    
    printf("%g\n", floor(ans+0.5));
}

int main()
{
    int T = readint();
    for(int i = 0; i < T; i++) solve(i);
    return 0;
}