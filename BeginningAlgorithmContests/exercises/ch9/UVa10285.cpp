// UVa10285 Longest Run on a Snowboard
// Rujia Liu
// 题意：在一个R*C整数矩阵上找一条递增最长路。每次只能往上下左右走一格。
// 算法：DAG上的最长路
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define REP(i,n) for(int i = 0; i < (n); i++)
const int maxn = 100 + 5;
int maze[maxn][maxn];
int R, C, d[maxn][maxn];

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int dp(int i, int j) {
  int& ans = d[i][j];
  if(ans > 0) return ans;
  ans = 1;
  for(int dir = 0; dir < 4; dir++) {
    int i2 = i + dx[dir], j2 = j + dy[dir];
    if(i2 >= 0 && i2 < R && j2 >= 0 && j2 < C && maze[i2][j2] > maze[i][j])
      ans = max(ans, dp(i2, j2) + 1);
  }
  return ans;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    char name[100];
    scanf("%s%d%d", name, &R, &C);
    REP(i,R) REP(j,C) scanf("%d", &maze[i][j]);
    int ans = 0;
    memset(d, 0, sizeof(d));
    REP(i,R) REP(j,C) ans = max(ans, dp(i,j));
    printf("%s: %d\n", name, ans);
  }
  return 0;
}
