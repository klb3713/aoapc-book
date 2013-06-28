// UVa10617 Again Palindromes
// Rujia Liu
// 题意：输入一个长度为N的字符串，删除0个或多个字符，剩下一个回文串。有多少种方案？最少得留一个字符。
// 算法：考虑两端的字符要不要删除。根据容斥原理，等于不删的方案数+删左边的方案数+删右边的方案数-删两边的方案数
// d[i][j]为S[i..j]的方案数。只有S[i]==S[j]的时候可以不删（方案数就是d[i+1][j-1]+1，这个1是只留两端）
// 删左边、右边和两边的方案数分别为d[i+1][j], d[i][j-1], d[i+1][j-1]
// 所以S[i]==S[j]时d[i][j]=d[i+1][j]+d[i][j-1]+1, 否则d[i][j]=d[i+1][j]+d[i][j-1]-d[i+1][j-1]。注意边界
#include<cstring>
#include<iostream>
#include<string>
using namespace std;

const int maxn = 100 + 5;
int n, vis[maxn][maxn];
long long d[maxn][maxn];
string S;

long long dp(int i, int j) {
  if(i > j) return 0;
  if(i == j) return 1;
  if(vis[i][j]) return d[i][j];
  vis[i][j] = 1;
  long long& ans = d[i][j];
  ans = dp(i+1,j) + dp(i,j-1);
  if(S[i] == S[j]) ans++; else ans -= dp(i+1,j-1);
  return ans;
}

int main() {
  int T;
  cin >> T;
  while(T--) {
    cin >> S;
    n = S.length();
    memset(vis, 0, sizeof(vis));
    cout << dp(0, n-1) << "\n";
  }
  return 0;
}
