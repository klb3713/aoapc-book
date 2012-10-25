// UVa10047 The Monocycle
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int INF = 1000000000;
const int maxr = 25 + 5;
const int maxc = 25 + 5;
int R, C, sr, sc, tr, tc;
char maze[maxr][maxc];

struct State {
  int r, c, dir, color;
  State(int r, int c, int dir, int color):r(r),c(c),dir(dir),color(color) {}
};

const int dr[] = {-1,0,1,0}; // north, west, south, east
const int dc[] = {0,-1,0,1};
int d[maxr][maxc][4][5], vis[maxr][maxc][4][5];

int ans;
queue<State> Q;

void update(int r, int c, int dir, int color, int v) {
  if(r < 0 || r >= R || c < 0 || c >= C) return; // 不能走出边界
  if(maze[r][c] == '.' && !vis[r][c][dir][color]) {
    Q.push(State(r, c, dir, color));
    vis[r][c][dir][color] = 1;
    d[r][c][dir][color] = v;
    if(r == tr && c == tc && color == 0) ans = min(ans, v); // 更新答案
  }
}

void bfs(State st) {
  d[st.r][st.c][st.dir][st.color] = 0;
  vis[st.r][st.c][st.dir][st.color] = 1;
  Q.push(st);
  while(!Q.empty()) {
    st = Q.front(); Q.pop();
    int v = d[st.r][st.c][st.dir][st.color] + 1;
    update(st.r, st.c, (st.dir+1)%4, st.color, v); // 左转
    update(st.r, st.c, (st.dir+3)%4, st.color, v); // 右转
    update(st.r+dr[st.dir], st.c+dc[st.dir], st.dir, (st.color+1)%5, v); // 前进
  }
}

int main() {
  int kase = 0;
  while(scanf("%d%d", &R, &C) == 2 && R && C) {
    for(int i = 0; i < R; i++) {
      scanf("%s", maze[i]);
      for(int j = 0; j < C; j++)
        if(maze[i][j] == 'S') { sr = i; sc = j; }
        else if(maze[i][j] == 'T') { tr = i; tc = j; }
    }
    maze[sr][sc] = maze[tr][tc] = '.';
    ans = INF;
    memset(vis, 0, sizeof(vis));
    bfs(State(sr, sc, 0, 0));

    if(kase > 0) printf("\n");
    printf("Case #%d\n", ++kase);
    if(ans == INF) printf("destination not reachable\n");
    else printf("minimum time = %d sec\n", ans);
  }
}
