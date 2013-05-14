// UVa10556 Biometrics
// 陈锋
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;

typedef long long int64;

struct Point {
  int64 x, y;
  Point(int64 x=0, int64 y=0):x(x) , y(y) { }
};

typedef Point Vector;
typedef vector<Point> Polygon;

Vector operator+ (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator- (Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator* (Vector A, int64 p) { return Vector(A.x*p, A.y*p); }

int64 Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
int64 Area2(Point A, Point B, Point C) { return Cross(B-A, C-A); }
int64 Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
int64 Length2(Vector A) { return Dot(A, A); }

int64 readint64() { int64 x; scanf("%lld", &x); return x; }

Point read_Point() { 
    int64 x = readint64(), y = readint64();
    return Point(x, y);
}

/********************************************************************/
int f;

void solve(){
    Polygon p1, p2;
    for(int i = 0; i < f; i++) p1.push_back(read_Point());
    for(int i = 0; i < f; i++) p2.push_back(read_Point());
    
    bool s = true;
    for(int i = 0; i < f; i++) {
        const Point& B = p1[i], A = p1[(i-1+f)%f], C = p1[(i+1)%f],
            B2 = p2[(i)%f], A2 = p2[(i-1+f)%f], C2 = p2[(i+1)%f];
        Vector BA = B-A, BC = B-C, BA2 = B2-A2, BC2 = B2-C2;
        int64 lBA = Length2(BA), lBC = Length2(BC), lBA2 = Length2(BA2), lBC2 = Length2(BC2);
        
        // lBA / lBC = lBA2 / lBC2 -> lBA * lBC2 == lBA2 * lBC
        // Area2(A, B, C) / Area2(A2, B2, C2) = lBA / lBA2 -> Area2(A,B,C) * lBA2 == lBA * Area2(A2,B2,C2)
        // Dot(BA, BC) * Dot(BA, BC) / Length2(A-B), Length2(C-B) 
  
        s = Dot(BA, BC) * Dot(BA, BC) * Length2(BA2) * Length2(BC2) == Dot(BA2, BC2) * Dot(BA2, BC2) * Length2(BA) * Length2(BC)
            && (lBA*lBC2 == lBA2*lBC) && (Area2(A,B,C)*lBA2 == lBA*Area2(A2,B2,C2));
        if(!s) break;
    }
    
    if(s) puts("similar");
    else puts("dissimilar");
}

int main()
{
    while(scanf("%d", &f) && f) solve();    
    return 0;
}