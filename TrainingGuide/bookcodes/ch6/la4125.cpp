// LA4125/UVa1075 Painter
// Rujia Liu
#include <cstdio>
#include <cstdlib>
#include <map>
#include<algorithm>
using namespace std;

typedef long long LL;

struct Point {
  int x, y;
  Point(int x = 0, int y = 0):x(x),y(y){}
  void read() { scanf("%d%d", &x, &y); }
  bool operator < (const Point& p) const {
    return x < p.x || x == p.x && y < p.y;
  }
  Point operator - (const Point& rhs) const {
    return Point(x - rhs.x, y - rhs.y);
  }
};

int icmp(LL x) {
  if(x == 0) return 0;
  return x > 0 ? 1 : -1;
}

inline LL Cross(Point p, Point p1, Point p2) {
  return (LL)(p1.x - p.x) * (LL)(p2.y - p.y) - (LL)(p1.y - p.y)*(LL)(p2.x - p.x);
}

// 由于线段相交判定执行次数较大，这里采用了一些小优化
inline bool SegmentIntersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
  if(min(a1.x, a2.x) > max(b1.x, b2.x)) return false; // 快速排除
  if(min(a1.y, a2.y) > max(b1.y, b2.y)) return false;
  if(max(a1.x, a2.x) < min(b1.x, b2.x)) return false;
  if(max(a1.y, a2.y) < min(b1.y, b2.y)) return false;
  LL c1 = Cross(a1, a2, b1), c2 = Cross(a1, a2, b2);
  if(icmp(c1) * icmp(c2) > 0) return false;
  LL c3 = Cross(b1, b2, a1), c4 = Cross(b1, b2, a2);
  return icmp(c3) * icmp(c4) <= 0;
}

int curx;
const double eps = 1e-6;

struct Segment {
  Point p1, p2;
  int no; // 三角形编号
  double d;
  Segment(Point p1, Point p2, int no):p1(p1),p2(p2),no(no) {
    d = (p2.y - p1.y) / (p2.x + eps - p1.x);
  }
  double y() const { return p1.y + d * (curx + eps - p1.x); }
  bool operator < (const Segment& rhs) const { return y() < rhs.y(); }
};

inline bool Intersect(const Segment& a, const Segment& b) {
  if(a.no == b.no) return false;
  return SegmentIntersection(a.p1, a.p2, b.p1, b.p2);
}

bool error;    // 是否已经出现相交线段
int max_depth; // 当前最大深度

const int INF = 200000;

// 本题这样做可以提高代码可读性，但不要在工程中这样使用，非常危险
#define L first   
#define depth second

// 扫描线类，用一个multimap实现
struct Scanline {
  multimap<Segment, int> line;
  typedef multimap<Segment, int>::iterator Pos;
  void init() {
    line.clear();
    line.insert(make_pair(Segment(Point(-INF,-INF), Point(INF,-INF), -1), 1));
    line.insert(make_pair(Segment(Point(-INF, INF), Point(INF, INF), -1), 0));
  }
  inline Pos Prev(const Pos& p) const { return --Pos(p); }
  inline Pos Next(const Pos& p) const { return ++Pos(p); }
  inline Pos Insert(const Segment& s, int d = 0) {
    Pos x = line.insert(make_pair(s, d));
    if(Intersect(x->L, Prev(x)->L) || Intersect(x->L, Next(x)->L)) error = true;
    return x;
  }  
  inline void Erase(const Pos& x) {
    if(Intersect(Prev(x)->L, Next(x)->L)) error = true;
    line.erase(x);
  }
} scanline;

struct Triangle {
  int no; // 编号
  Point P[3];
  Scanline::Pos p12, p13, p23;
  void read(int no) {
    this->no = no;
    for(int i = 0; i < 3; i++) scanf("%d%d", &P[i].x, &P[i].y);
    sort(P, P+3);
  }
  // 更新x1和x2的depth。其中x1是p12和p13中y较小的那个，x2是另一个（即Next(x1)=x2）
  void updateDepth(const Scanline::Pos& x1, Scanline::Pos& x2) {
    int d = scanline.Prev(x1)->depth + 1;
    max_depth = max(max_depth, d);
    x1->depth = d;
    x2->depth = d - 1;
  }
  // 处理第v个结点
  void process(int v) {
    if(v == 0) {
      p12 = scanline.Insert(Segment(P[0], P[1], no));
      p13 = scanline.Insert(Segment(P[0], P[2], no));
      scanline.Next(p12) == p13 ? updateDepth(p12, p13) : updateDepth(p13, p12);
    }
    else if(v == 1) {
      p23 = scanline.Insert(Segment(P[1], P[2], no), p12->depth);
      scanline.Erase(p12);
    }
    else {
      scanline.Erase(p13);
      scanline.Erase(p23);
    }
  }
};

struct Event {
  int x, t, v; // x坐标，三角形编号和顶点编号
  Event(){}
  Event(int x, int t, int v):x(x),t(t),v(v){}
  bool operator < (const Event& rhs) const {
    return x < rhs.x || x == rhs.x && v < rhs.v;
  }
};

const int maxn = 100000 + 10; // 最大三角形个数
Triangle tri[maxn];
Event events[maxn*3];

int main() {
  int n, kase = 0;
  while(scanf("%d",&n) == 1 && n >= 0) {
    error = false;
    max_depth = 1;
    scanline.init();
    for(int i = 0; i < n; i++) {
      tri[i].read(i);
      for(int j = 0; j < 3; j++)
        events[i*3+j] = Event(tri[i].P[j].x, i, j);
    }
    sort(events, events+n*3);
    for(int i = 0; i < n*3; i++) {
      curx = events[i].x;
      tri[events[i].t].process(events[i].v);
      if(error) break;
    }
    if(!error) printf("Case %d: %d shades\n", ++kase, max_depth);
    else printf("Case %d: ERROR\n", ++kase);
  }
  return 0;
}
