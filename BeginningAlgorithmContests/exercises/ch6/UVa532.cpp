// UVa532 Dungeon Master
// Rujia Liu
// 题意：三维迷宫中给定起点（字符S）和终点（字符E），墙是'#'，空格是'.'，求最短路长度
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

struct State {
  int l, r, c;
  State(int l, int r, int c):l(l),r(r),c(c) {}
};

const int maxn = 30 + 5;
const int dl[] = {1,-1,0,0,0,0};
const int dr[] = {0,0,1,-1,0,0};
const int dc[] = {0,0,0,0,1,-1};
int L, R, C, d[maxn][maxn][maxn], vis[maxn][maxn][maxn];
char maze[maxn][maxn][maxn];

int bfs(int l1, int r1, int c1) {
  queue<State> Q;
  d[l1][r1][c1] = 0;
  vis[l1][r1][c1] = 1;
  Q.push(State(l1, r1, c1));
  while(!Q.empty()) {
    State s = Q.front(); Q.pop();
    for(int i = 0; i < 6; i++) {
      int newl = s.l + dl[i];
      int newr = s.r + dr[i];
      int newc = s.c + dc[i];
      if(newl >= 0 && newl < L && newr >= 0 && newr < R && newc >= 0 && newc < C && maze[newl][newr][newc] != '#' && !vis[newl][newr][newc]) {
        Q.push(State(newl, newr, newc));
        vis[newl][newr][newc] = 1;
        d[newl][newr][newc] = d[s.l][s.r][s.c] + 1;
        if(maze[newl][newr][newc] == 'E') return d[newl][newr][newc];
      }
    }
  }
  return -1;
}

int main() {
  while(scanf("%d%d%d", &L, &R, &C) == 3 && L) {
    int l1, r1, c1;
    for(int i = 0; i < L; i++)
      for(int j = 0; j < R; j++) {
        scanf("%s", maze[i][j]);
        for(int k = 0; k < C; k++)
          if(maze[i][j][k] == 'S') { l1 = i; r1 = j; c1 = k; }
      }
    memset(vis, 0, sizeof(vis));
    int ans = bfs(l1, r1, c1);
    if(ans >= 0) printf("Escaped in %d minute(s).\n", ans);
    else printf("Trapped!\n");
  }
  return 0;
}
