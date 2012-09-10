#include<stdio.h>
#include<string.h>
const int MAXN = 1000;
int n;

int mat[MAXN][MAXN], vis[MAXN][MAXN];
void dfs(int x, int y) {
  if(!mat[x][y] || vis[x][y]) return;     // 曾经访问过这个格子，或者当前格子是白色
  vis[x][y] = 1;                          // 标记(x,y)已访问过
  dfs(x-1,y-1); dfs(x-1,y); dfs(x-1,y+1);
  dfs(x  ,y-1);             dfs(x  ,y+1);
  dfs(x+1,y-1); dfs(x+1,y); dfs(x+1,y+1); // 递归访问周围的八个格子
}

int main() {
  char s[MAXN + 10];
  memset(mat, 0, sizeof(mat));  // 所有格子都初始化为白色，包括周围一圈的虚拟格子
  memset(vis, 0, sizeof(vis));  // 所有格子都没有访问过
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%s", s);
    for(int j = 0; j < n; j++)
      mat[i+1][j+1] = s[j]-'0'; // 把图像往中间移动一点，空出一圈白格子
  }
  int count = 0;
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= n; j++)
      if(!vis[i][j] && mat[i][j]) { count++; dfs(i,j); } // 找到没有访问过的黑格
  printf("%d\n", count);
  return 0;
}
