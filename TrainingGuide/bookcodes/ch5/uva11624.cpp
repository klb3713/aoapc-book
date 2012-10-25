// UVa11624 Fire!
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
const int maxr = 1000 + 5;
const int maxc = 1000 + 5;
int R, C;
char maze[maxr][maxc];

struct Cell {
  int r, c;
  Cell(int r, int c):r(r),c(c) {}
};

const int dr[] = {-1,1,0,0};
const int dc[] = {0,0,-1,1};
int d[maxr][maxc][2], vis[maxr][maxc][2];

queue<Cell> Q;
void bfs(int kind) {
  while(!Q.empty()) {
    Cell cell = Q.front(); Q.pop();
    int r = cell.r, c = cell.c;
    for(int dir = 0; dir < 4; dir++) {
      int nr = r + dr[dir], nc = c + dc[dir];
      if(nr >= 0 && nr < R && nc >= 0 && nc < C && maze[nr][nc] == '.' && !vis[nr][nc][kind]) {
        Q.push(Cell(nr, nc));
        vis[nr][nc][kind] = 1;
        d[nr][nc][kind] = d[r][c][kind] + 1;
      }
    }
  }
}

int ans;
void check(int r, int c) {
  if(maze[r][c] != '.' || !vis[r][c][0]) return; // 必须是Joe可达的边界格子
  if(!vis[r][c][1] || d[r][c][0] < d[r][c][1]) ans = min(ans, d[r][c][0] + 1); // Joe必须先于火到达
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &R, &C);
    int jr, jc;
    vector<Cell> fires;
    for(int i = 0; i < R; i++) {
      scanf("%s", maze[i]);
      for(int j = 0; j < C; j++)
        if(maze[i][j] == 'J') { jr = i; jc = j; maze[i][j] = '.'; }
        else if(maze[i][j] == 'F') { fires.push_back(Cell(i,j)); maze[i][j] = '.'; }
    }
    memset(vis, 0, sizeof(vis));

    // Joe
    vis[jr][jc][0] = 1; d[jr][jc][0] = 0;
    Q.push(Cell(jr, jc));
    bfs(0);

    // Fire
    for(int i = 0; i < fires.size(); i++) {
      vis[fires[i].r][fires[i].c][1] = 1;
      d[fires[i].r][fires[i].c][1] = 0;
      Q.push(fires[i]);
    }
    bfs(1);

    // 计算答案
    ans = INF;
    for(int i = 0; i < R; i++) { check(i,0); check(i,C-1); }
    for(int i = 0; i < C; i++) { check(0,i); check(R-1,i); }
    if(ans == INF) printf("IMPOSSIBLE\n"); else printf("%d\n", ans);
  }
  return 0;
}
