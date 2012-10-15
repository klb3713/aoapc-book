// UVa11520 Fill the Square
// Rujia Liu
#include<cstdio>
#include<cstring>
const int maxn = 10 + 5;
char grid[maxn][maxn];
int n;
int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%s", grid[i]);
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++) if(grid[i][j] == '.') {//没填过的字母才需要填
        for(char ch = 'A'; ch <= 'Z'; ch++) { 		//按照字典序依次尝试
          bool ok = true;
          if(i>0 && grid[i-1][j] == ch) ok = false; 	//和上面的字母冲突
          if(i<n-1 && grid[i+1][j] == ch) ok = false;
          if(j>0 && grid[i][j-1] == ch) ok = false;
          if(j<n-1 && grid[i][j+1] == ch) ok = false;
          if(ok) { grid[i][j] = ch; break; } //没有冲突，填进网格，停止继续尝试
        }
      }
    printf("Case %d:\n", kase);
    for(int i = 0; i < n; i++) printf("%s\n", grid[i]);
  }
  return 0;
}
