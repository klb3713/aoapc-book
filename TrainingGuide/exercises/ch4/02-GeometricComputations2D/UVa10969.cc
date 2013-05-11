// UVa10969 Sweet Dream
// 陈锋
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;

const double eps = 1e-10;
int dcmp(double x) { if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1; }

const double PI = acos(-1), TWO_PI = PI * 2;

double NormalizeAngle(double rad, double center = PI) {
  return rad - TWO_PI * floor((rad + PI - center) / TWO_PI);
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x) , y(y) { }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double angle(Vector v) { return atan2(v.y, v.x); }

struct Circle {
    Point center;
    double radius;
    
    void getIntersection(const Circle& c2, vector<double>& rad) const {
        Vector vc = c2.center - center;
        double d = Length(vc);
        if(dcmp(d) == 0) return;
        if(dcmp(radius + c2.radius - d) < 0) return;
        if(dcmp(fabs(radius - c2.radius) - d) > 0) return;
        
        double a = angle(vc);
        double da = acos((radius*radius + d*d - c2.radius*c2.radius) / (2*radius*d));
        rad.push_back(NormalizeAngle(a-da));
        rad.push_back(NormalizeAngle(a+da));
    }
};

int readint() {
    int x;
    scanf("%d", &x);
    return x;
}

void read_point(Point& p) { scanf("%lf%lf", &(p.x), &(p.y)); }
/********************************************************************/
const int maxn = 100 + 5;
int n;
Circle cs[maxn];
bool vis[maxn];

// 覆盖点p的最上层的圆
bool covered(Point p, int c) {
    for(int i = n-1; i > c; i--)
    {
        int d = dcmp(Length(cs[i].center-p) - cs[i].radius);
        if(d <= 0) return true;
    }
    return false;
}

void solve(){
    n = readint();
    for(int i = 0; i < n; i++) {
        scanf("%lf", &(cs[i].radius));
        read_point(cs[i].center);
    }
    fill_n(vis, n, false);
    
    double ans = 0.0;
    
    for(int i = 0; i < n; i++) {
        // 考虑圆i被切割成的各个圆弧。把圆周当做区间来处理，起点是0，终点是2PI
        vector<double> rad;
        const Circle& c = cs[i];
        rad.push_back(0);
        rad.push_back(PI);
        for(int j = 0; j < n; j++) c.getIntersection(cs[j], rad);
        sort(rad.begin(), rad.end());
        rad.push_back(TWO_PI);

        for(int j = 0; j < rad.size() - 1; j++) {
            double mid = (rad[j] + rad[j+1]) / 2.0; // 圆弧中点相对于圆i圆心的极角
            Point midPoint(c.center.x + cos(mid)* c.radius, c.center.y + sin(mid) * c.radius);
            bool ic = covered(midPoint, i);
            double a = rad[j+1] - rad[j];
            
            // printf("i = %d, [%.3lf, %.3lf], (%.3lf-%.3lf)\n", i, midPoint.x, midPoint.y, rad[j+1], rad[j]);
            
            if(!ic) ans += NormalizeAngle(a) * c.radius;
        }
    }

    printf("%.3lf\n", ans);
}

int main()
{
    int T = readint();
    for(int i = 0; i < T; i++)
        solve();
    
    return 0;
}