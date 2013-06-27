// UVa10192 Compromise
// Rujia Liu
// 题意：输入两个字符串序列，求最长公共子序列，要求输出方案
// 算法：LCS
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;

string A[maxn], B[maxn];
int n, m, d[maxn][maxn];

int LCS() {
  memset(d, 0, sizeof(d));
  for(int i = 1; i <= n; i++)
    for(int j = 1; j <= m; j++) {
      if(A[i-1] == B[j-1]) d[i][j] = d[i-1][j-1] + 1;
      else d[i][j] = max(d[i][j-1], d[i-1][j]);
    }
  return d[n][m];
}

bool read() {
  string s;
  n = m = 0;
  while(cin >> s) {
    if(s[0] == '#') break;
    A[n++] = s;
  }
  if(n == 0) return false;
  while(cin >> s) {
    if(s[0] == '#') break;
    B[m++] = s;
  }
  return true;
}

bool first;
void print(int i, int j) {
  if(i == 0 || j == 0) return;
  if(A[i-1] == B[j-1]) {
    print(i-1, j-1);
    if(first) first = false; else cout << " ";
    cout << A[i-1];
  }
  else if(d[i][j-1] > d[i-1][j]) print(i, j-1);
  else print(i-1, j);
}

void solve() {
  int ans = LCS();
  first = true;
  print(n, m);
  cout << "\n";
}

int main() {
  int kase = 0;
  while(read()) solve();
  return 0;
}
