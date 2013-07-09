// UVa10721 Bar Codes
// Rujia Liu
// 题意：输入n, k, m，输出有多少个条形码满足：共有k个条，宽度之和为n，每个条宽度均为1~m的正整数。
// 算法：设答案为d[k][n]，则d[i][j]=sum{d[i-1][j-c] | 1<=c<=min{j,k}}
#include<iostream>
#include<cstring>
using namespace std;

const int maxk = 50 + 5;
const int maxn = 50 + 5;
long long d[maxk][maxn];

int main() {
  int n, k, m;
  while(cin >> n >> k >> m) {
    memset(d, 0, sizeof(d));
    d[0][0] = 1;
    for(int i = 1; i <= k; i++)
      for(int j = 1; j <= n; j++) {
        d[i][j] = 0;
        for(int c = 1; c <= m && c <= j; c++)
          d[i][j] += d[i-1][j-c];
      }
    cout << d[k][n] << "\n";
  }
  return 0;
}
