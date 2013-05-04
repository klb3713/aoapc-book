// UVa11800 Determine the Shape
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
  int64 x, y;
  Point(int64 x=0, int64 y=0):x(x),y(y) { }
  Point(const Point& rhs) : x(rhs.x), y(rhs.y) { }
};

typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, int64 p) { return Vector(A.x*p, A.y*p); }
bool operator == (const Point& a, const Point &b) {
  return a.x == b.x &&  a.y == b.y;
}
bool operator < (const Point& p1, const Point& p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}
int64 Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
int64 Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }

Point read_point() {
    int64 x, y;
    scanf("%lld%lld", &x, &y);
    return Point(x,y);
}

void print_point(const Point& p) {
    printf("[%lld, %lld]", p.x, p.y);
}

bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) {
  int64 c1 = Cross(a2-a1,b1-a1), c2 = Cross(a2-a1,b2-a1), c3 = Cross(b2-b1,a1-b1), c4=Cross(b2-b1,a2-b1);
  return c1 * c2 < 0 &&  c3 * c4 < 0;
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

/**********************************************************/

int64 Len2(const Vector& v){ return Dot(v, v); };

void solve(int k)
{
    printf("Case %d: ", k);
    vector<Point> p;
    for(int i = 0; i < 4; i++)
        p.push_back(read_point());
    vector<Point> points = ConvexHull(p);
    if(points.size() != 4) { puts("Ordinary Quadrilateral"); return; }
    
    Point& A = points[0];
    Point& B = points[1];
    Point& C = points[2];
    Point& D = points[3];
   
    /* A D
       B C     */
        
    Vector BA = B - A,  DA = D - A, CD = C - D, CB = C - B;
    int64 lBA = Len2(BA), lCD = Len2(CD), lDA = Len2(DA), lCB = Len2(CB);
    
    if(Dot(BA, DA) == 0 && Dot(DA, CD) == 0 && Dot(CB, CD) == 0)
    {
        if(lBA == lCB) puts("Square");
        else puts("Rectangle");
        return;
    }
    
    if(BA == CD && CB == DA)
    {
        if(lBA == lDA) puts("Rhombus");
        else puts("Parallelogram");
        return;
    }
    
    if(Cross(BA, CD) == 0 || Cross(DA, CB) == 0)
        puts("Trapezium");
    else
        puts("Ordinary Quadrilateral");
}

int main()
{
    int T = readint();
    for(int i = 0; i < T; i++)
        solve(i+1);
    return 0;
}
