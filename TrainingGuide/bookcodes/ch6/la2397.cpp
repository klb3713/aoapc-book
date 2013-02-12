// LA2397/UVa1060 Collecting Luggage
// Rujia Liu
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const double eps = 1e-10;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }

bool operator < (const Point& a, const Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator == (const Point& a, const Point &b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }
double Length(Vector A) { return sqrt(Dot(A, A)); }

bool SegmentProperIntersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
  double c1 = Cross(a2-a1,b1-a1), c2 = Cross(a2-a1,b2-a1),
  c3 = Cross(b2-b1,a1-b1), c4=Cross(b2-b1,a2-b1);
  return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

bool OnSegment(const Point& p, const Point& a1, const Point& a2) {
  return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}

int isPointInPolygon(const Point& p, Point* poly, int n){
  int wn = 0;
  for(int i = 0; i < n; i++){
    const Point& p1 = poly[i];
    const Point& p2 = poly[(i+1)%n];
    if(p1 == p || p2 == p || OnSegment(p, p1, p2)) return -1; // 在边界上
    int k = dcmp(Cross(p2-p1, p-p1));
    int d1 = dcmp(p1.y - p.y);
    int d2 = dcmp(p2.y - p.y);
    if(k > 0 && d1 <= 0 && d2 > 0) wn++;
    if(k < 0 && d2 <= 0 && d1 > 0) wn--;
  }
  if (wn != 0) return 1; // 内部
  return 0; // 外部
}

const int maxn = 100 + 10;
const int INF = 1000000000;

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

int n;
Point startp, belt[maxn]; // 为了方便，belt[n]是起点，belt[n+1]是终点
double vl, vp, perimeter, len[maxn];
Dijkstra solver;

// 边a-b是否被挡住
bool isBlocked(int a, int b) {
  for(int i = 0; i < n+2; i++)
    if(i != a && i != b && OnSegment(belt[i], belt[a], belt[b])) return true; // 中间不能有其他点
  for(int i = 0; i < n; i++)
    if(SegmentProperIntersection(belt[i], belt[(i+1)%n], belt[a], belt[b])) return true; // 不能和多边形的边规范相交
  Point midp = (belt[a] + belt[b]) * 0.5;
  if(isPointInPolygon(midp, belt, n) == 1) return true; // 整条线段在多边形内
  return false;
}

// 判断是否可以在时刻t拿到行李
bool check(double t) {
  solver.init(n+2); // 0~n-1是传送带顶点，n是起点，n+1是终点

  // 计算行李位置，存放到belt[n+1]
  double dist = fmod(vl*t, perimeter);
  for(int i = 0; i < n; i++) {
    if(len[i] >= dist) {
      belt[n+1] = belt[i] + (belt[(i+1)%n] - belt[i]) * (dist / len[i]);
      break;
    }
    dist -= len[i];
  }

  // 构图
  for(int i = 0; i < n+2; i++)
    for(int j = i+1; j < n+2; j++) {
      double d = Length(belt[i]-belt[j]);
      if(d > eps && isBlocked(i, j)) continue;
      solver.AddEdge(i, j, d);
      solver.AddEdge(j, i, d);
    }
  solver.dijkstra(n);
  return solver.d[n+1] <= vp*t;
}

int getSecond(double t) {
  return (int)floor(t * 60 + 0.5);
}

int main() {
  int kase = 0;
  while(scanf("%d", &n) == 1 && n > 0) {
    for(int i = 0; i < n; i++) scanf("%lf%lf", &belt[i].x, &belt[i].y);
    scanf("%lf%lf%lf%lf", &startp.x, &startp.y, &vl, &vp);
    perimeter = 0;
    double closest = 1e9;
    for(int i = 0; i < n; i++) {
      closest = min(closest, Length(startp - belt[i])); // 更新人到最近顶点的距离
      len[i] = Length(belt[i] - belt[(i+1)%n]);
      perimeter += len[i]; // 累加周长
    }
    belt[n] = startp;
    double L = 0, R = (closest + perimeter / 2) / vp; // 上界为人走到最近顶点再走半周长所需要的时间
    while(getSecond(L) != getSecond(R)) { // 这样写最保险。L和R很接近不代表四舍五入到“秒”后一定一样
      double M = L + (R-L)/2;
      if(check(M)) R = M; else L = M;
    }
    int t = getSecond(L);
    printf("Case %d: Time = %d:%02d\n", ++kase, t / 60, t % 60);
  }
  return 0;
}
