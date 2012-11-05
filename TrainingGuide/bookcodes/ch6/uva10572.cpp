// UVa10572 Black and White
// Rujia Liu
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

int nrows, ncols, has_sol;
char partial[8][9]; // 输入网格
char grid[8][8], sol[8][8]; // 当前正在填的网格和解网格

struct State {
  char color[8];       // 各列格子颜色
  char up_left;        // 左上方格子颜色（用来判断是否出现2x2同色子网格）
  char comp[8];        // 各格子连通分量
  char ncomp;          // 连通分量总数
  char ncolor_comp[2]; // 白连通分量个数和黑连通分量个数

  // 计算状态的最小表示
  void normalize() {
    int rep[10];
    memset(rep, -1, sizeof(rep));
    ncomp = ncolor_comp[0] = ncolor_comp[1] = 0;
    for (int i = 0; i < ncols; i++) {
      if (rep[comp[i]] < 0) {
        rep[comp[i]] = ncomp++;
        ncolor_comp[color[i]]++;
      }
      comp[i] = rep[comp[i]];
    }
  }

  // 把所有编号为b的连通分量改成a
  void merge(int a, int b) {
    if (a == b) return;
    for (int i = 0; i < ncols; i++)
      if (comp[i] == b) comp[i] = a;
  }

  // 正好不超过32位无符号整数范围
  unsigned int encode() {
    unsigned int key = 0;
    for (int i = 0; i < ncols; i++)
      key = key * 16 + color[i] * 8 + comp[i];
    return key;
  }
};

// 动态规划所用状态值表。只记录了不强制涂色（即force_color<0）时的值
map<unsigned, int> memo[8][8][2]; 

const int ch[] = { 'o', '#' };

// 当前要涂格子(row, col)，状态为S，必须涂force_color颜色。返回解的个数
int rec(int row, int col, State& S, int force_color) {
  if (col == ncols) { col = 0; row++; }
  S.normalize(); // 计算最小表示

  if (row == nrows) {
    if (S.ncolor_comp[0] > 1 || S.ncolor_comp[1] > 1) return 0;
    if (has_sol == 0) {
      has_sol = 1;
      for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; j++)
          sol[i][j] = grid[i][j];
    }
    return 1;
  }

  // 如果左格子和上格子颜色不同，则左上方格子的颜色是无关紧要的，统一设为0，减少状态
  if (row > 0 && col > 0 && S.color[col] != S.color[col-1])
    S.up_left = 0;

  // 只有不强制涂色（force_color<0）时key才有意义
  unsigned int key;
  if (force_color < 0) {
    key = S.encode();
    if (memo[row][col][S.up_left].count(key) != 0)
      return memo[row][col][S.up_left][key];
  }

  int res = 0;

  // 当前格子涂color这种颜色
  for(int color = 0; color < 2; color++) {
    if (force_color == 1 - color) continue; // 和force_color矛盾
    if (partial[row][col] == ch[1-color]) continue; // 和输入矛盾
    if (row > 0 && col > 0 && S.color[col-1] == color && S.color[col] == color && S.up_left == color) continue; // 出现2x2同色子网格

    State T = S;
    T.color[col] = color;
    T.up_left = S.color[col];
    T.comp[col] = (row > 0 && S.color[col] == color) ? S.comp[col] : S.ncomp; // 初始化新状态第col列的连通分量编号
    if (col > 0 && T.color[col-1] == color) T.merge(T.comp[col-1], T.comp[col]); // 如果颜色和左格子相同，则设置为左格子的连通分量

    grid[row][col] = ch[color];

    if (row > 0 && S.color[col] == 1-color) { // 检查上方格子是否为独立连通分量      
      if (find(T.comp, T.comp+ncols, S.comp[col]) == T.comp+ncols) { // 该连通分量已经消失
        if (S.ncolor_comp[1-color] > 1 || row < nrows-2) continue; // 如果color还有其他连通分量存在，或者至少还有两行需要涂，则无法继续
        res += rec(row, col+1, T, color); // 可以继续，但以后强制涂color
        continue;
      }
    }

    res += rec(row, col+1, T, force_color);
  }

  if (force_color < 0)
    memo[row][col][S.up_left][key] = res;
  return res;
}


int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%d%d", &nrows, &ncols);
    for(int i = 0; i < nrows; i++) scanf("%s", partial[i]);

    State S;
    memset(&S, 0, sizeof(S));
    S.normalize();
    for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
        for (int k = 0; k < 2; k++)
          memo[i][j][k].clear();

    has_sol = 0;
    printf("%d\n", rec(0, 0, S, -1));
    if (has_sol) {
      for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < ncols; j++)
          putchar(sol[i][j]);
        putchar('\n');
      }
    }
    printf("\n");
  }
  return 0;
}
