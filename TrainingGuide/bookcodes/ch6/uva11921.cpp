// UVa11921 Save the Princess
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

const double INF = 1e9;
const int maxn = 5200; // 每两个圆最多有4条切线，总点数不会超过50*49/2*4 + 50*2*2 + 2 =5102

struct Edge {
  int from, to;
  double dist;
};

struct HeapNode {
  double d;
  int u;
  bool operator < (const HeapNode& rhs) const {
    return d > rhs.d;
  }
};

struct Dijkstra {
  int n, m;
  vector<Edge> edges;
  vector<int> G[maxn];
  bool done[maxn];    // 是否已永久标号
  double d[maxn];     // s到各个点的距离
  int p[maxn];        // 最短路中的上一条弧

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, double dist) {
    edges.push_back((Edge){from, to, dist});
    m = edges.size();
    G[from].push_back(m-1);
  }

  void dijkstra(int s) {
    priority_queue<HeapNode> Q;
    for(int i = 0; i < n; i++) d[i] = INF;
    d[s] = 0;
    memset(done, 0, sizeof(done));
    Q.push((HeapNode){0, s});
    while(!Q.empty()) {
      HeapNode x = Q.top(); Q.pop();
      int u = x.u;
      if(done[u]) continue;
      done[u] = true;
      for(int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if(d[e.to] > d[u] + e.dist) {
          d[e.to] = d[u] + e.dist;
          p[e.to] = G[u][i];
          Q.push((HeapNode){d[e.to], e.to});
        }
      }
    }
  }
};

#include<cmath>

const double eps = 1e-8;
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

// 理论上这个“小于”运算符是错的，因为可能有三个点a, b, c, a和b很接近（即a<b好b<a都不成立），b和c很接近，但a和c不接近
// 所以使用这种“小于”运算符的前提是能排除上述情况
bool operator < (const Point& a, const Point& b) {
  return dcmp(a.x - b.x) < 0 || (dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) < 0);
}

bool operator == (Point A, Point B) {
  return dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) == 0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
Vector Rotate(Vector A, double rad) {
  return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}

double angle(Vector v) {
  return atan2(v.y, v.x);
}

Point GetLineProjection(Point P, Point A, Point B) {
  Vector v = B-A;
  return A+v*(Dot(v, P-A) / Dot(v, v));
}

double DistanceToSegment(const Point& P, const Point& A, const Point& B) {
  if(A == B) return Length(P-A);
  Vector v1 = B - A, v2 = P - A, v3 = P - B;
  if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
  else if(dcmp(Dot(v1, v3)) > 0) return Length(v3);
  else return fabs(Cross(v1, v2)) / Length(v1);
}

// 过点p到圆C的切线。v[i]是第i条切线的向量。返回切线条数
int getTangents(Point p, Point c, double r, vector<Vector>& v) {
  Vector u = c - p;
  double dist = Length(u);
  if(dist < r) return 0;
  else if(dcmp(dist - r) == 0) { // p在圆上，只有一条切线
    v.push_back(Rotate(u, PI/2));
    return 1;
  } else {
    double ang = asin(r / dist);
    v.push_back(Rotate(u, -ang));
    v.push_back(Rotate(u, +ang));
    return 2;
  }
}

// 点到圆的切点。返回切点个数
// 可以对getTangents函数稍做修改求出切点，不过这里偷了个懒，求出圆心在切线上的投影，就是切点
int getTangentPoints(Point p, Point c, double r, vector<Point>& out) {
  vector<Vector> v;
  int cnt = getTangents(p, c, r, v);
  for(int i = 0; i < cnt; i++)
    out.push_back(GetLineProjection(c, p, p+v[i]));
  return cnt;
}

// 取圆(C, r)弧度为rad的点
Point getCirclePoint(Point C, double r, double rad) {
  return Point(C.x + cos(rad)*r, C.y + sin(rad)*r);
}

// 返回圆和圆的切线的条数。-1表示无穷多条切线。
// a[i]和b[i]分别是第i条切线在圆(c1, r1)和圆(c2, r2)上的切点
int getTangentPoints(Point c1, double r1, Point c2, double r2, Point* a, Point* b) {
  int cnt = 0;
  if(r1 < r2) { swap(c1, c2); swap(r1, r2); swap(a, b); }
  int d2 = (c1.x-c2.x)*(c1.x-c2.x) + (c1.y-c2.y)*(c1.y-c2.y);
  int rdiff = r1-r2;
  int rsum = r1+r2;
  if(d2 < rdiff*rdiff) return 0; // 内含

  double base = atan2(c2.y-c1.y, c2.x-c1.x);
  if(d2 == 0 && r1 == r2) return -1; // 无限多条切线
  if(d2 == rdiff*rdiff) { // 内切，1条切线
    a[cnt] = getCirclePoint(c1, r1, base); b[cnt] = getCirclePoint(c2, r2, base); cnt++;
    return 1;
  }
  // 有外公切线
  double ang = acos((r1-r2) / sqrt(d2));
  a[cnt] = getCirclePoint(c1, r1, base+ang); b[cnt] = getCirclePoint(c2, r2, base+ang); cnt++;
  a[cnt] = getCirclePoint(c1, r1, base-ang); b[cnt] = getCirclePoint(c2, r2, base-ang); cnt++;
  if(d2 == rsum*rsum) { // 一条内公切线
    a[cnt] = getCirclePoint(c1, r1, base); b[cnt] = getCirclePoint(c2, r2, PI+base); cnt++;
  }
  else if(d2 > rsum*rsum) { // 两条内公切线
    double ang = acos((r1+r2) / sqrt(d2));
    a[cnt] = getCirclePoint(c1, r1, base+ang); b[cnt] = getCirclePoint(c2, r2, PI+base+ang); cnt++;
    a[cnt] = getCirclePoint(c1, r1, base-ang); b[cnt] = getCirclePoint(c2, r2, PI+base-ang); cnt++;
  }
  return cnt;
}

////////////// 题目相关
#include<map>
const int maxp = 50 + 10;

int n;                    // 障碍的个数
Point C[maxp], src, dest; // 障碍圆心，起点和终点
double r[maxp];           // 障碍半径

vector<Edge> e;           // 临时边数组
vector<Point> points;     // 用来构图的点（起点、终点、切点）
map<Point, int> idx;      // 点到图的结点编号的映射

Dijkstra dijkstra;

// 返回点p映射到的编号
int ID(Point p) {
  if(idx.count(p)) return idx[p];
  points.push_back(p);
  idx[p] = points.size() - 1;
}

// 检查点a到点b的线段是否不和任意圆相交，且最多和maxtangent个圆相切。
// 如果是，加边a-b
void checkSegment(Point a, Point b, int maxtangent) {
  for(int i = 0; i < n; i++) {
    int d = dcmp(DistanceToSegment(C[i], a, b) - r[i]);
    if(d < 0) return; // 圆i和线段ab相交
    if(d == 0) { if(maxtangent-- == 0) return; } // 圆i和线段ab相切，统计个数
  }
  int ia = ID(a), ib = ID(b);
  if(ia >= 0 && ib >= 0 && ia != ib) e.push_back((Edge){ia, ib, Length(a-b)});
}

// 检查起点或终点到每个圆的两条切线（因为起点和终点严格在圆外，所以恰好有两条切线）
void checkPointToCircle(Point p) {
  for(int i = 0; i < n; i++) {
    vector<Point> t;
    getTangentPoints(p, C[i], r[i], t);
    checkSegment(p, t[0], 1);
    checkSegment(p, t[1], 1);
  }
}

// 检查两个圆的最多四条切线
// 本题中的圆和圆只会外切和相离，但为了演示模板的用法，仍然使用了“未删节版”的圆和圆求切线的方法 ;-)
void checkCircleToCircle() {
  for(int i = 0; i < n; i++)
    for(int j = i+1; j < n; j++) {
      Point a[4], b[4];
      int cnt = getTangentPoints(C[i], r[i], C[j], r[j], a, b);
      for(int k = 0; k < cnt; k++)
        checkSegment(a[k], b[k], 2);
    }
}

// 同一个圆上相邻两点连一条边
void checkPointOnCircle() {
  for(int i = 0; i < n; i++) {
    vector<double> on; // 圆i上所有点的极角
    int m = points.size();
    for(int j = 0; j < m; j++)
      if(dcmp(Length(points[j] - C[i]) - r[i]) == 0) on.push_back(angle(points[j] - C[i]));
    if(on.size() < 2) continue; // 至少要有两个点才有意义

    sort(on.begin(), on.end());
    on.erase(unique(on.begin(), on.end()), on.end());
    m = on.size();
    for(int j = 0; j < m; j++) {
      Point a = getCirclePoint(C[i], r[i], on[j]);
      Point b = getCirclePoint(C[i], r[i], on[(j+1)%m]);
      double dist = NormalizeAngle(on[(j+1)%m] - on[j]) * r[i];
      int ia = ID(a), ib = ID(b);
      if(ia >= 0 && ib >= 0 && ia != ib) e.push_back((Edge){ia, ib, dist});
    }
  }
}

// p是否至少在两个圆周上（这样的话，这个点将不能连边）
bool isForbidden(Point p) {
  int cnt = 0;
  for(int i = 0; i < n; i++)
    if(dcmp(Length(C[i] - p) - r[i]) == 0)
      if(++cnt == 2) return true;
  return false;
}

/*
  根据题意：
  1. 起点和终点严格在圆外
  2. 障碍圆不会相交，但可能外切，而切点不能通过。
  假定两个障碍圆外切。虽然可以“绕着切点走”而不穿过切点，但这样做肯定不是最优的
  所以“在至少2个圆周上”的点肯定不在最优路径上，属于“废点” ;-)

  那么，是否可以在ID(p)里直接判断p是否至少在2个圆周上，如果是则返回-1，代表这个点不能要？不行。
  假定有一个圆上有三个点a, b, c，其中b在至少2个圆周上。
  如果早早的删除了点b，在checkPointOnCircle()中会认为圆上只有两个点a和c，然后连一条边。但这条边实际上穿过了点b，因此非法！

  正确的做法是在points数组中保留这些点，只是不要添加与它们邻接的边
*/
double solve() {
  idx.clear();
  points.clear();
  e.clear();
  int s = ID(src);
  int t = ID(dest);

  checkSegment(src, dest, 0);
  checkPointToCircle(src);
  checkPointToCircle(dest);
  checkCircleToCircle();
  checkPointOnCircle();

  dijkstra.init(points.size());
  for(int i = 0; i < e.size(); i++) {
    int a = e[i].from, b = e[i].to;
    if(isForbidden(points[a]) || isForbidden(points[b])) continue; // 点a或点b不能连边
    double d = e[i].dist;
    dijkstra.AddEdge(a, b, d);
    dijkstra.AddEdge(b, a, d);
  }

  dijkstra.dijkstra(s);
  return dijkstra.d[t];
}

int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%lf%lf%lf%lf%d", &src.x, &src.y, &dest.x, &dest.y, &n);
    for(int i = 0; i < n; i++)
      scanf("%lf%lf%lf", &C[i].x, &C[i].y, &r[i]);
    printf("Case %d: %.9lf\n", kase, solve());
  }
  return 0;
}
