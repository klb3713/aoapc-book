// LA3029 City Game
// Rujia Liu
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1000;
int mat[maxn][maxn], up[maxn][maxn], left[maxn][maxn], right[maxn][maxn];
int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    int m, n;
    scanf("%d%d", &m, &n);
    for(int i = 0; i < m; i++)
      for(int j = 0; j < n; j++) {
        int ch = getchar();
        while(ch != 'F' && ch != 'R') ch = getchar();
        mat[i][j] = ch == 'F' ? 0 : 1;
      }

    int ans = 0;
    for(int i = 0; i < m; i++) { // 从上到下逐行处理
      int lo = -1, ro = n;
      for(int j = 0; j < n; j++) // 从左到右扫描，维护up和left
        if(mat[i][j] == 1) { up[i][j] = left[i][j] = 0; lo = j; } 
        else {
          up[i][j] = i == 0 ? 1 : up[i-1][j] + 1;
          left[i][j] = i == 0 ? lo+1 : max(left[i-1][j], lo+1);
        }
      for(int j = n-1; j >= 0; j--) // 从右到左扫描，维护right并更新答案
        if(mat[i][j] == 1) { right[i][j] = n; ro = j; }
        else {
          right[i][j] = i == 0 ? ro-1 : min(right[i-1][j], ro-1);
          ans = max(ans, up[i][j]*(right[i][j]-left[i][j]+1));
        }
    }
    printf("%d\n", ans*3); // 题目要求输出最大面积乘以3后的结果
  }
  return 0;
}
