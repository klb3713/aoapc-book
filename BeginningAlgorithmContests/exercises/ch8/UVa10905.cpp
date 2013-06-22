// UVa10905 Children's Game
// Rujia Liu
// 题意：有一种游戏，给出N个正整数，要求计算出一种把这些数连接起来的方案使结果最大。比如有4个数123,124,56,90,那么可以连出以下的结果：1231245690, 1241235690, 5612312490, 9012312456, 9056124123 等。实际上有24种结果，但是可以肯定是9056124123是其中最大的。 
// 算法：按照a+b>b+a的规则排序
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

bool cmp(const string& a, const string& b) {
  return a+b > b+a;
}

const int maxn = 50 + 5;
string s[maxn];

int main() {
  int n;
  while(cin >> n && n) {
    for(int i = 0; i < n; i++) cin >> s[i];
    sort(s, s+n, cmp);
    for(int i = 0; i < n; i++) cout << s[i];
    cout << "\n";
  }
  return 0;
}
