// LA2572/UVa1308 Viva Confetti
// Rujia Liu
#include<cmath>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;

const double eps = 5 * 1e-13;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

const double PI = acos(-1);
const double TWO_PI = PI * 2;

double NormalizeAngle(double rad, double center = PI) {
  return rad - TWO_PI * floor((rad + PI - center) / TWO_PI);
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }

double angle(Vector v) {
  return atan2(v.y, v.x);
}

// 交点相对于圆1的极角保存在rad中
void getCircleCircleIntersection(Point c1, double r1, Point c2, double r2, vector<double>& rad) {
  double d = Length(c1 - c2);
  if(dcmp(d) == 0) return; // 不管是内含还是重合，都不相交
  if(dcmp(r1 + r2 - d) < 0) return;
  if(dcmp(fabs(r1-r2) - d) > 0) return;

  double a = angle(c2 - c1);
  double da = acos((r1*r1 + d*d - r2*r2) / (2*r1*d));
  rad.push_back(NormalizeAngle(a-da));
  rad.push_back(NormalizeAngle(a+da));
}

const int maxn = 100 + 5;
int n;
Point center[maxn];
double radius[maxn];
bool vis[maxn];

// 覆盖点p的最上层的圆
int topmost(Point p) {
  for(int i = n-1; i >= 0; i--)
    if(Length(center[i]-p) < radius[i]) return i;
  return -1;
}

int main() {
  while(cin >> n) {
    if(!n) break;
    for(int i = 0; i < n; i++) {
      double x, y, r;
      cin >> x >> y >> r;
      center[i] = Point(x, y);
      radius[i] = r;
    }
    memset(vis, 0, sizeof(vis));
    for(int i = 0; i < n; i++) {
      // 考虑圆i被切割成的各个圆弧。把圆周当做区间来处理，起点是0，终点是2PI
      vector<double> rad;
      rad.push_back(0);
      rad.push_back(PI*2);
      for(int j = 0; j < n; j++)
        getCircleCircleIntersection(center[i], radius[i], center[j], radius[j], rad);
      sort(rad.begin(), rad.end());

      for(int j = 0; j < rad.size(); j++) {
        double mid = (rad[j] + rad[j+1]) / 2.0; // 圆弧中点相对于圆i圆心的极角
        for(int side = -1; side <= 1; side += 2) {
          double r2 = radius[i] - side*eps; // 往里面或者外面稍微一动一点点
          int t = topmost(Point(center[i].x + cos(mid)*r2, center[i].y + sin(mid)*r2));
          if(t >= 0) vis[t] = true;
        }
      }
    }
    int ans = 0;
    for(int i = 0; i < n; i++) if(vis[i]) ans++;
    cout << ans << "\n";
  }
  return 0;
}
