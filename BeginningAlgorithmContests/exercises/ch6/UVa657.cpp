// UVa657 The die is cast
// Rujia Liu
// 题意：给一个图案，其中'.'表示背景，非'.'字符组成的连通块为筛子。每个筛子里又包含两种字符，其中'X'组成的连通块表示筛子上的点
// 统计每个筛子里有多少个“X”连通块
// 算法：首先用DFS找出两类连通块，即筛子（'.'与'X'）和点（'X'），类别用0和1表示，然后统计0类连通块和1类连通块之间的包含关系，最后输出结果
// 在代码中，cnt[i]为第i类连通块的个数，idx[i][r][c]为格子(r,c)处第i类连通分量的编号
// enclose[i][j]表示编号为i的第0类连通块是否包含编号为j的第1类连通块
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50;   // 图片边长的最大值
const int maxd = 1000; // 筛子的最大个数
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

char pic[maxn][maxn];
int h, w, idx[2][maxn][maxn], cnt[2]; 
int enclose[maxd][maxd*6];

bool is_type(int type, char ch) {
  if(type == 0) return ch != '.'; // 筛子（包括点）
  return ch == 'X'; // 点
}

// DFS找第type类联通块，赋予编号id
void dfs(int r, int c, int type, int id) {
  if(r < 0 || r >= h || c < 0 || c >= w) return;
  if(!is_type(type, pic[r][c])) return;
  if(idx[type][r][c] > 0) return;
  idx[type][r][c] = id;
  for(int d = 0; d < 4; d++)
    dfs(r+dr[d], c+dc[d], type, id);
}

// 标记(r,c)处的0类连通块包含编号为id的1类连通块
void mark(int r, int c, int id) {
  if(r >= 0 && r < h && c >= 0 && c < w)
    enclose[idx[0][r][c]][id] = 1;
}

int main() {
  int kase = 0;
  while(scanf("%d%d", &w, &h) == 2 && w) {
    for(int i = 0; i < h; i++)
      scanf("%s", pic[i]);

    // DFS求连通块
    memset(idx, 0, sizeof(idx));
    cnt[0] = cnt[1] = 0;
    for(int i = 0; i < h; i++)
      for(int j = 0; j < w; j++) 
        for(int t = 0; t < 2; t++) {
          if(idx[t][i][j] == 0 && is_type(t, pic[i][j])) dfs(i, j, t, ++cnt[t]);
        }

    // 计算包含关系
    memset(enclose, 0, sizeof(enclose));
    for(int i = 0; i < h; i++)
      for(int j = 0; j < w; j++)
        if(pic[i][j] == 'X')
          for(int d = 0; d < 4; d++)
            mark(i+dr[d], j+dc[d], idx[1][i][j]);

    // 统计点数。注意两类连通块均从1开始编号
    int ans[maxd];
    for(int i = 1; i <= cnt[0]; i++) {
      ans[i] = 0;
      for(int j = 1; j <= cnt[1]; j++)
        if(enclose[i][j]) ans[i]++;
    }
    sort(ans+1, ans+cnt[0]+1);

    // 输出。注意行末不要输出多余空格
    printf("Throw %d\n", ++kase);
    for(int i = 1; i < cnt[0]; i++)
      printf("%d ", ans[i]);
    printf("%d\n\n", ans[cnt[0]]);
  }
  return 0;
}
