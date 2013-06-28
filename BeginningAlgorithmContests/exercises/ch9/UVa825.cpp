// UVa825 Walking on the Safe Side
// Rujia Liu
// 题意：n*m网格里有一些障碍，求从左上到右下的路径条数。只能往右和往下走
// 算法：动态规划。d[i][j]为从左上到(i,j)的路径条数，用刷表法比较好写。题目没说规模，实测m,n<=200
#include<iostream>
#include<cstring>
#include<string>
#include<sstream>
using namespace std;

const int maxn = 200;
int a[maxn][maxn], d[maxn][maxn];

int main() {
  string line;
  int T, m, n;
  cin >> T;
  while(T--) {
    cin >> m >> n;
    getline(cin, line);
    memset(a, 0, sizeof(a));
    memset(d, 0, sizeof(d));
    for(int i = 0; i < m; i++) {
      getline(cin, line);
      stringstream ss(line);
      int j;
      ss >> j;
      while(ss >> j) a[i][j-1] = 1;
    }
    if(a[0][0] == 0) d[0][0] = 1;
    for(int i = 0; i < m; i++)
      for(int j = 0; j < n; j++) {
        if(i + 1 < m && a[i+1][j] == 0) d[i+1][j] += d[i][j];        
        if(j + 1 < n && a[i][j+1] == 0) d[i][j+1] += d[i][j];        
      }
    cout << d[m-1][n-1] << "\n";
    if(T) cout << "\n";
  }

  return 0;
}
