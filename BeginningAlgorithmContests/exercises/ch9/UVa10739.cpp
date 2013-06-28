// UVa10739 String to Palindrome
// Rujia Liu
// 题意：输入一个小写字母组成的字符串，可以插入、删除和修改字符。用最少的修改次数变成回文串
// 算法：插入是不必的。设d[i][j]为子串S[i..j]需要修改的最少次数
// 如果S[i]==S[j]则d[i][j]=d[i+1][j-1]，否则可以替换(d[i+1][j-1]+1)或者删除某一个(d[i+1][j]+1或者d[i][j-1]+1)
#include<cstdio>
#include<cstring>
#include<iostream>
#include<string>
using namespace std;

const int maxn = 1000 + 5;
int n, vis[maxn][maxn], d[maxn][maxn];
string S;

int dp(int i, int j) {
  if(i >= j) return 0;
  if(vis[i][j]) return d[i][j];
  vis[i][j] = 1;
  int& ans = d[i][j];
  if(S[i] == S[j]) ans = dp(i+1,j-1);
  else { ans = min(dp(i+1,j), dp(i,j-1)); ans = min(ans, dp(i+1,j-1)) + 1; }
  return ans;
}

int main() {
  int T;
  cin >> T;
  for(int kase = 1; kase <= T; kase++) {
    cin >> S;
    n = S.length();
    memset(vis, 0, sizeof(vis));
    printf("Case %d: %d\n", kase, dp(0, n-1));
  }
  return 0;
}
