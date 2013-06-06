// UVa784 Maze Exploration
// Rujia Liu
// 题意：输入一个迷宫，从*开始遍历，把可达点标记为字符#
#include<cstdio>
#include<cstring>
const int maxn = 100 + 5;
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

int R;
char maze[maxn][maxn];

void dfs(int r, int c) {
  if(r < 0 || r >= R || c < 0 || maze[r][c] == '\n') return;
  if(maze[r][c] == 'X' || maze[r][c] == '#') return;
  maze[r][c] = '#';
  for(int d = 0; d < 4; d++)
    dfs(r+dr[d], c+dc[d]);
}

int main() {
  int T;
  scanf("%d\n", &T);
  while(T--) {
    R = 0;
    for(;;) {
      fgets(maze[R++], maxn, stdin);
      if(maze[R-1][0] == '_') break;
    }
    for(int i = 0; i < R; i++)
      for(int j = 0; j < strlen(maze[i]); j++)
        if(maze[i][j] == '*') dfs(i, j);
    for(int i = 0; i < R; i++)
      printf("%s", maze[i]); // 自带回车
  }
  return 0;
}
