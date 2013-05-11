// UVa11928 The Busy Dog
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;

struct Point {
  int x, y;
  Point(int x=0, int y=0):x(x),y(y) { }
};

typedef Point Vector;

typedef vector<Point> Polygon;

Vector operator - (Point A, Point B) {
  return Vector(A.x-B.x, A.y-B.y);
}

bool operator == (const Point& A, const Point& B) {
  return A.x == B.x && A.y == B.y;
}

int Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
int Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }

bool OnSegment(Point p, Point a1, Point a2) {
  return Cross(a1-p, a2-p) == 0 && Dot(a1-p, a2-p) < 0;
}

int getWindingNumber(Point p, const Polygon& v, bool& on){
  int wn = 0;
  int n = v.size();
  for(int i = 0; i < n; i++){
    if(OnSegment(p, v[i], v[(i+1)%n]) || p == v[i]) { on = true; return 0; }
    int k = Cross(v[(i+1)%n]-v[i], p-v[i]);
    int d1 = v[i].y - p.y;
    int d2 = v[(i+1)%n].y - p.y;
    if(k > 0 && d1 <= 0 && d2 > 0) wn++;
    if(k < 0 && d2 <= 0 && d1 > 0) wn--;
  }
  on = false;
  return wn;
}

Point read_point() {
  int x, y;
  scanf("%d%d", &x, &y);
  return Point(x, y);
}

int main() {
  int n;
  while(scanf("%d", &n) == 1 && n) {
    Polygon v;
    Point p = read_point();
    for(int i = 0; i < n; i++)
      v.push_back(read_point());
    bool on;
    int wn = getWindingNumber(p, v, on);
    if(on) printf("Ouch!\n");
    else if(wn > 0) printf("+%d\n", wn);
    else printf("%d\n", wn);
  }
  return 0;
}
