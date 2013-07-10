// UVa10996 Go
// 陈锋
#include<climits>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cassert>
#include<cstdlib>
#include<map>
using namespace std;

const int maxn = 32;

struct Point{ 
    int x, y; 
    Point(int a=0, int b=0) : x(a), y(b) {}        
};

vector<Point> adj(const Point& p) {
    vector<Point> r;
    r.push_back(Point(p.x-1, p.y));
    r.push_back(Point(p.x+1, p.y));
    r.push_back(Point(p.x, p.y-1));
    r.push_back(Point(p.x, p.y+1));
    return r;
}

enum CellStat{BORDER=-1, EMPTY=0, BLACK=1, WHITE=2 };
int n, m, mark[maxn][maxn]; // 表示已经被包围的
CellStat board[maxn][maxn];
char colors[] = {"#_BW"};
int scale(int x) { return x + (n+1)/2; }
void clearMark() { memset(mark, 0, sizeof(mark)); }

void dump() {
    int sz = (n+1)/2;
    for(int x = -sz; x <= sz; x++){
        for(int y = sz; y >= -sz; y--) 
            putchar(colors[board[scale(x)][scale(y)]+1]);
        puts("");
    }
    puts("====================================================");
}

// 检查p是不是已经被color一方捕获
bool check_capture(Point p, CellStat color) {
    int& mk = mark[p.x][p.y];
    if(mk) return true;
    mk = 1;
    int bd = board[p.x][p.y];
    if(bd == BORDER) return true;
    if(bd == color) return true;
    if(bd == EMPTY) return false;
    
    vector<Point> a = adj(p);
    for(int j = 0; j < 4; j++)
        if(!check_capture(a[j], color)) return false;
    return true;
}

void do_capture(Point p, CellStat color, int *score) {
    CellStat cedCoor = (CellStat)(3 ^ color); // 反色
    CellStat& bd = board[p.x][p.y];
    if(bd != cedCoor) return;
    score[color]++;
    bd = EMPTY;
    
    vector<Point> a = adj(p);
    for(int j = 0; j < 4; j++)
        do_capture(a[j], color, score);
}

bool check_own(Point p, CellStat color) { // 检查p是不是已经被color围起来的空格
    CellStat bd = board[p.x][p.y];
    int& mk = mark[p.x][p.y];
    if(bd == color) return true;
    if(bd == BORDER) return true;
    if(mk) return true;
    mk = 1;
    
    if(bd != EMPTY) return false;
    vector<Point> a = adj(p);
    for(int j = 0; j < 4; j++) 
        if(!check_own(a[j], color)) return false;
    
    return true;
}

void solve() {
    memset(board, BORDER, sizeof(board));
    char buf[16];
    int score[4] = {0};
    
    int sz = (n-1)/2;
    for(int x = -sz; x <= sz; x++){
        for(int y = sz; y >= -sz; y--) {
            board[scale(x)][scale(y)] = EMPTY;
        }
    }
    
    for(int i = 0; i < m; i++) {
        int x, y;
        char c;
        scanf("%c(%d,%d) ", &c, &x, &y);
        x = scale(x); y = scale(y);               
        CellStat color = (c == 'B' ? BLACK : WHITE);
        board[x][y] = color;
        
        Point p(x,y);
        vector<Point> a = adj(p);
        for(int j = 0; j < 4; j++) {
            clearMark();
            if(check_capture(a[j], color)) { clearMark(); do_capture(a[j], color, score); }
        }
        
        // dump();
    }
    
    for(int x = -sz; x <= sz; x++){
        for(int y = sz; y >= -sz; y--) {
            int i = scale(x), j = scale(y);
            CellStat bd = board[i][j];
            if(bd != EMPTY) continue;
            Point p(i, j);
            clearMark();
            if(check_own(p, BLACK)) score[BLACK]++;
            clearMark();
            if(check_own(p, WHITE)) score[WHITE]++;
        }
    }
    
    printf("%d %d\n", score[BLACK], score[WHITE]);
}

int main()
{
    while(true) {
        scanf("%d%d ", &n, &m);
        if(!n) break;
        solve();
    }
}