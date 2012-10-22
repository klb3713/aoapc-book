// UVa12296 Pieces and Discs
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

const double eps = 1e-8;
double dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

typedef vector<Point> Polygon;

Vector operator + (Vector A, Vector B) {
  return Vector(A.x+B.x, A.y+B.y);
}

Vector operator - (Point A, Point B) {
  return Vector(A.x-B.x, A.y-B.y);
}

Vector operator * (Vector A, double p) {
  return Vector(A.x*p, A.y*p);
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
double Length2(Vector A) { return Dot(A, A); }

Point GetLineIntersection(Point P, Vector v, Point Q, Vector w) {
  Vector u = P-Q;
  double t = Cross(w, u) / Cross(v, w);
  return P+v*t;
}

bool OnSegment(Point p, Point a1, Point a2) {
  return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}

// 多边形的有向面积
double PolygonArea(Polygon poly) {
  double area = 0;
  int n = poly.size();
  for(int i = 1; i < n-1; i++)
    area += Cross(poly[i]-poly[0], poly[(i+1)%n]-poly[0]);
  return area/2;
}

// cut with directed line A->B, return the left part
// may return a single point or a line segment
Polygon CutPolygon(Polygon poly, Point A, Point B) {
  Polygon newpoly;
  int n = poly.size();
  for(int i = 0; i < n; i++) {
    Point C = poly[i];
    Point D = poly[(i+1)%n];
    if(dcmp(Cross(B-A, C-A)) >= 0) newpoly.push_back(C);
    if(dcmp(Cross(B-A, C-D)) != 0) {
      Point ip = GetLineIntersection(A, B-A, C, D-C);
      if(OnSegment(ip, C, D)) newpoly.push_back(ip);
    }
  }
  return newpoly;
}

int isPointInPolygon(Point p, Polygon v){
  int wn = 0;
  int n = v.size();
  for(int i = 0; i < n; i++){
    if(OnSegment(p, v[i], v[(i+1)%n])) return -1; // 在边界上
    int k = dcmp(Cross(v[(i+1)%n]-v[i], p-v[i]));
    int d1 = dcmp(v[i].y - p.y);
    int d2 = dcmp(v[(i+1)%n].y - p.y);
    if(k > 0 && d1 <= 0 && d2 > 0) wn++;
    if(k < 0 && d2 <= 0 && d1 > 0) wn--;
  }
  if (wn != 0) return 1; // 内部
  return 0; // 外部
}

// 点在圆心内。圆周上不算
bool isInCircle(Point p, Point center, double R) {
  return dcmp(Length2(p-center) - R*R) < 0;
}

// 直线AB和圆心为C，半径为r的圆的交点
// 返回交点个数，t1, t2分别为两个交点在直线方程中的参数，p1和p2为交点本身
int getLineCircleIntersection(Point A, Point B, Point C, double r, double& t1, double& t2){
  // 初始方程：(A.x + t(B.x - A.x) - C.x)^2 + (A.y + t(B.y - A.y) - C.y)^2 = r^2
  // 整理得：(at + b)^2 + (ct + d)^2 = r^2
  double a = B.x - A.x;
  double b = A.x - C.x;
  double c = B.y - A.y;
  double d = A.y - C.y;
  // 展开得：(a^2 + c^2)t^2 + 2(ab + cd)t + b^2 + d^2 - r^2 = 0，即et^2 + ft + g = 0
  double e = a * a + c * c;
  double f = 2 * (a * b + c * d);
  double g = b * b + d * d - r * r;
  double delta = f * f - 4 * e * g; // 判别式
  if(dcmp(delta) < 0) return 0; // 相离
  if(dcmp(delta) == 0){ // 相切
    t1 = t2 = -f / (2 * e);
    return 1;
  }
  t1 = (-f - sqrt(delta)) / (2 * e);
  t2 = (-f + sqrt(delta)) / (2 * e);
  return 2;
}

// 圆和线段是否相交（相切不算）。线段不考虑端点
bool CircleIntersectSegment(Point A, Point B, Point p, double R) {
  double t1, t2;
  int c = getLineCircleIntersection(A, B, p, R, t1, t2);
  if(c <= 1) return false;
  if(dcmp(t1) > 0 && dcmp(t1-1) < 0) return true; // 端点在圆上
  if(dcmp(t2) > 0 && dcmp(t2-1) < 0) return true;
  return false;
}

/////////// 题目相关
vector<Polygon> pieces, new_pieces;

void cut(int x1, int y1, int x2, int y2) {
  new_pieces.clear();
  for(int i = 0; i < pieces.size(); i++) {
    Polygon left = CutPolygon(pieces[i], Point(x1, y1), Point(x2, y2));
    Polygon right = CutPolygon(pieces[i], Point(x2, y2), Point(x1, y1));
    if(left.size() >= 3) new_pieces.push_back(left);
    if(right.size() >= 3) new_pieces.push_back(right);
  }
  pieces = new_pieces;
}

bool DiscIntersectPolygon(Polygon poly, Point p, double R) {
  if(isPointInPolygon(p, poly) != 0) return true;
  if(isInCircle(poly[0], p, R)) return true;
  int n = poly.size();
  for(int i = 0; i < n; i++) {
    if(CircleIntersectSegment(poly[i], poly[(i+1)%n], p, R)) {
      return true; // 不考虑线段端点
    }
    if(isInCircle((poly[i]+poly[(i+1)%n])*0.5, p, R)) {
      return true; // 两个端点都在圆上
    }
  }
  return false;
}

void query(Point p, int R) {
  vector<double> ans;
  for(int i = 0; i < pieces.size(); i++) {
    if(DiscIntersectPolygon(pieces[i], p, R)) {
      ans.push_back(fabs(PolygonArea(pieces[i])));
    }
  }
  printf("%d", ans.size());
  sort(ans.begin(), ans.end());
  for(int i = 0; i < ans.size(); i++)
    printf(" %.2lf", ans[i]);
  printf("\n");
}

int main() {
  int n, m, L, W;
  while(scanf("%d%d%d%d", &n, &m, &L, &W) == 4 && n) {
    pieces.clear();

    Polygon bbox;
    bbox.push_back(Point(0, 0));
    bbox.push_back(Point(L, 0));
    bbox.push_back(Point(L, W));
    bbox.push_back(Point(0, W));
    pieces.push_back(bbox);

    for(int i = 0; i < n; i++) {
      int x1, y1, x2, y2;
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      cut(x1, y1, x2, y2);
    }

    for(int i = 0; i < m; i++) {
      int x, y, R;
      scanf("%d%d%d", &x, &y, &R);
      query(Point(x, y), R);
    }
    printf("\n");
  }  
  return 0;
}
