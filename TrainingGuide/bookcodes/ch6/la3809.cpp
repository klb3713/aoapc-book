// LA3809/UVa1065 Raising the Roof
// Rujia Liu
// 寻找top时改用简单循环寻找，效率稍低但代码简单
#include<cstdio>
#include<cmath>
#define REP(i,n) for(int i = 0; i < (n); ++i)

const double eps = 1e-8;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point3 {
  int x, y, z;
  Point3(int x=0, int y=0, int z=0):x(x),y(y),z(z) { }
};

typedef Point3 Vector3;

Vector3 operator - (const Point3& A, const Point3& B) {
  return Vector3(A.x-B.x, A.y-B.y, A.z-B.z);
}

int Dot(const Vector3& A, const Vector3& B) { return A.x*B.x + A.y*B.y + A.z*B.z; }
double Length(const Vector3& A) { return sqrt(Dot(A, A)); }
Vector3 Cross(const Vector3& A, const Vector3& B) { return Vector3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x); }

#include<cstdlib>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 300 + 10;
const int maxt = 1000 + 10;

Point3 p[maxn];
int n, m;
int t[maxt][3];
Vector3 normal[maxt];    // 三角形i的法向量
double d[maxt];          // 三角形i的点法式为Dot(normal[i], p) = d
double area_ratio[maxt]; // 三角形i的投影面积乘以area_ratio[i]就是实际面积

// 输入中有在竖直平面内（即normal[i].z=0）的三角形，但主算法会自动忽略它们，不用担心area_ratio[i]不存在
void init() {
  for(int i = 0; i < m; i++) {
    Point3 p0 = p[t[i][0]], p1 = p[t[i][1]], p2 = p[t[i][2]];
    normal[i] = Cross(p1 - p0, p2 - p0);
    d[i] = Dot(normal[i], p0);
    if(normal[i].z != 0)
      area_ratio[i] = fabs((double)Length(normal[i]) / normal[i].z); 
  }
}

inline double getTriangleZ(int idx, double x, double y) {
  return (d[idx] - normal[idx].x * x - normal[idx].y * y) / normal[idx].z;
}

struct Event {
  int id;   // 涉及到的三角形编号
  double y; // 与扫描线交点的y坐标
  Event(int id, double y):id(id),y(y) {}
  bool operator < (const Event& rhs) const {
    return y < rhs.y;
  }
};

double solve() {
  // 离散化
  vector<double> sx;
  for(int i = 1; i <= n; i++) sx.push_back(p[i].x);
  REP(i,m) REP(j,m) REP(a,3) REP(b,3) {
    // 求pa-pb和qa-qb投影到XY平面后的交点。直接解参数方程
    Point3 pa = p[t[i][a]];
    Point3 pb = p[t[i][(a+1)%3]];
    Point3 qa = p[t[j][b]];
    Point3 qb = p[t[j][(b+1)%3]];
    int dpx = pb.x - pa.x;
    int dpy = pb.y - pa.y;
    int dqx = qb.x - qa.x;
    int dqy = qb.y - qa.y;
    int deno = dpx * dqy - dpy * dqx;
    if(deno == 0) continue;
    double t = (double)(dqy*(qa.x-pa.x)+dqx*(pa.y-qa.y)) / deno;
    double s = (double)(dpy*(qa.x-pa.x)+dpx*(pa.y-qa.y)) / deno;
    if(t > 1 || t < 0 || s > 1 || s < 0) continue;
    sx.push_back(pa.x + t * dpx);
  }
  sort(sx.begin(), sx.end());
  sx.erase(unique(sx.begin(), sx.end()), sx.end());

  double ans = 0;
  for(int i = 0; i < sx.size()-1; i++) {
    // 扫描线位于x = xx
    double xx = (sx[i] + sx[i+1]) / 2;

    // 计算扫描线穿过的三角形集合，为每个三角形创建“进入”和“离开”事件
    vector<Event> events;
    REP(j,m) if(normal[j].z != 0) REP(a,3) { // 忽略竖直平面内的三角形
      Point3 pa = p[t[j][a]];
      Point3 pb = p[t[j][(a+1)%3]];
      // 计算扫描线x = xx和pa-pb在平面XY上投影的交点
      if(pa.x == pb.x) continue; // 竖直线段
      if(!(min(pa.x, pb.x) <= sx[i] && max(pa.x, pb.x) >= sx[i+1])) continue; // 不在竖直条内
      double y = pa.y + (pb.y - pa.y) * (xx - pa.x) / (pb.x - pa.x); // 解方程得到
      events.push_back(Event(j, y));
    }
    if(events.empty()) continue;

    // 按照y递增的顺序处理事件
    int inside[maxt];
    memset(inside, 0, sizeof(inside));
    sort(events.begin(), events.end());
    for(int j = 0; j < events.size()-1; j++) {
      inside[events[j].id] ^= 1;
      if(fabs(events[j].y - events[j+1].y) < eps) continue; // y相同的事件要等到所有inside更新完毕后才能处理

      // 投影梯形的面积等于中线乘以高
      double projection_area = (sx[i+1] - sx[i]) * (events[j+1].y - events[j].y);

      // 在下一个事件发生之前，哪个三角形在最上面？
      int top = -1;
      double topz = -1e9;
      double yy = (events[j].y + events[j+1].y) / 2; // 测试y坐标中点，计算zz误差比较小
      for(int k = 0; k < m; k++) if(inside[k]) {
        double zz = getTriangleZ(k, xx, yy);
        if(zz > topz) { topz = zz; top = k; } // 更新最上面的三角形编号top
      }

      // 投影部分面积乘以比例系数等于实际面积
      if(top >= 0) ans += area_ratio[top] * projection_area;
    }
  }
  return ans;
}

int main() {
  int kase = 0;
  while(scanf("%d%d", &n, &m) == 2 && n > 0) {
    for(int i = 1; i <= n; i++) scanf("%d%d%d", &p[i].x, &p[i].y, &p[i].z); // 顶点编号为1~n
    for(int i = 0; i < m; i++) scanf("%d%d%d", &t[i][0], &t[i][1], &t[i][2]);
    init();
    double ans = solve();
    printf("Case %d: %.2lf\n\n", ++kase, ans);
  }
  return 0;
}
