// UVa10422 Knights in FEN
// Rujia Liu
// 题意： 5x5棋盘上12个黑马，12个白马和1个空格。每次可以把一个马移动到空格中（遵守国际象棋中马的移动规则）。
// 用最少步数把棋盘变成一个特定样子（见题图）。如果10步内无解则输出无解
// 算法：IDA*，启发函数为：如果还有d个马没走到目标位置，至少还要d步

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int dmax;
const int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
const int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
const char* goal[] = {"11111", "01111", "00 11", "00001", "00000"};
char board[6][6];
int sx, sy;

int solution_diff() {
  int d = 0;
  for(int i = 0; i < 5; i++)
    for(int j = 0; j < 5; j++)
      if(goal[i][j] != board[i][j] && board[i][j] != ' ') d++;
  return d;
}

// dfs函数返回后(board, sx, sy)保持不变
bool dfs(int d) {
  int diff = solution_diff();
  if(diff == 0) return true;
  if(d + diff > dmax) return false; // IDA*剪枝
  for(int i = 0; i < 8; i++) {
    int nx = sx + dx[i];
    int ny = sy + dy[i];
    if(nx >= 0 && nx < 5 && ny >= 0 && ny < 5) {
      swap(board[sx][sy], board[nx][ny]);
      swap(sx, nx); swap(sy, ny);
      bool ans = dfs(d+1);
      swap(sx, nx); swap(sy, ny);
      swap(board[sx][sy], board[nx][ny]);
      if(ans) return true;
    }
  }
  return false;
}

void solve() {
  for(int i = 0; i < 5; i++)
    for(int j = 0; j < 5; j++)
      if(board[i][j] == ' ') { sx = i; sy = j; }
  for(dmax = 0; dmax <= 10; dmax++)
    if(dfs(0)) { printf("Solvable in %d move(s).\n", dmax); return; }
  printf("Unsolvable in less than 11 move(s).\n");  
}

int main() {
  int T;
  scanf("%d\n", &T);
  while(T--) {
    for(int i = 0; i < 5; i++) fgets(board[i], 10, stdin);
    solve();
  }
  return 0;
}

