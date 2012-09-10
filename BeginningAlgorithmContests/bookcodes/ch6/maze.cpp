#include<stdio.h>
#include<string.h>
#define MAXN 105
int n, m, xs, ys, xt, yt;
int maze[MAXN][MAXN], vis[MAXN][MAXN], fa[MAXN][MAXN], dist[MAXN][MAXN], last_dir[MAXN][MAXN], num[MAXN][MAXN];

int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
char name[] = "UDLR";

int q[MAXN*MAXN];
void bfs(int x, int y) {
  int front=0, rear=0, d, u;
  u = x*m+y;
  vis[x][y] = 1; fa[x][y] = u; dist[x][y] = 0;
  q[rear++] = u;
  while(front<rear) {
    u = q[front++];    
    x = u/m; y = u%m;
    for(d = 0; d < 4; d++) {
      int nx = x+dx[d], ny = y+dy[d];
      if(nx>=0 && nx<n && ny>=0 && ny<m && maze[nx][ny] && !vis[nx][ny]) {
        int v = nx*m+ny;
        q[rear++] = v;
        vis[nx][ny] = 1;
        fa[nx][ny] = u;
        dist[nx][ny] = dist[x][y]+1;
        last_dir[nx][ny] = d;
      }
    }
  }
}

void print_path(int x, int y) {
  int fx = fa[x][y]/m;
  int fy = fa[x][y]%m;
  if(fx != x || fy != y) {
    print_path(fx, fy);
    putchar(name[last_dir[x][y]]);
  }
}

int dir[MAXN*MAXN];
void print_path2(int x, int y) {
  int c = 0;
  for(;;) {
    int fx = fa[x][y]/m;
    int fy = fa[x][y]%m;
    if(fx == x && fy == y) break;
    dir[c++] = last_dir[x][y];
    x = fx;
    y = fy;
  }
  while(c--)
    putchar(name[dir[c]]);
}

int main() {
  int i, j;
  scanf("%d%d%d%d%d%d", &n, &m, &xs, &ys, &xt, &yt);
  for(i = 0; i < n; i++)
    for(j = 0; j < m; j++)
      scanf("%d", &maze[i][j]);
  memset(vis, 0, sizeof(vis));
  bfs(xs, ys);
  print_path(xt, yt);
  putchar('\n');
  print_path2(xt, yt);
  putchar('\n');
  return 0;
}
