// UVa439 Knight Moves
// Rujia Liu
// 题意：输入标准国际象棋棋盘上的两个格子，求马最少需要多少步从起点跳到终点
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

struct State {
  int r, c;
  State(int r, int c):r(r),c(c) {}
};

const int dr[] = {-2,-2,-1,-1, 1,1, 2,2};
const int dc[] = {-1, 1,-2, 2,-2,2,-1,1};
int d[8][8], vis[8][8];

int bfs(int r1, int c1, int r2, int c2) {
  if(r1 == r2 && c1 == c2) return 0;
  queue<State> Q;
  d[r1][c1] = 0;
  vis[r1][c1] = 1;
  Q.push(State(r1, c1));
  while(!Q.empty()) {
    State s = Q.front(); Q.pop();
    for(int i = 0; i < 8; i++) {
      int newr = s.r + dr[i];
      int newc = s.c + dc[i];
      if(newr >= 0 && newr < 8 && newc >= 0 && newc < 8 && !vis[newr][newc]) {
        Q.push(State(newr, newc));
        vis[newr][newc] = 1;
        d[newr][newc] = d[s.r][s.c] + 1;
        if(newr == r2 && newc == c2) return d[newr][newc];
      }
    }
  }
  return -1;
}

int main() {
  char s[9], t[9];
  while(scanf("%s%s", s, t) == 2) {
    memset(vis, 0, sizeof(vis));
    int ans = bfs(s[0]-'a', s[1]-'1', t[0]-'a', t[1]-'1');
    printf("To get from %s to %s takes %d knight moves.\n", s, t, ans);
  }
  return 0;
}
