// UVa11054 Wine trading in Gergovia
// Rujia Liu
/* 
题意：
数轴上有n个人。从左到右第i个人的想买a[i]瓶酒（a[i]<0表示想卖-a[i]瓶酒）。
把酒从一个运给相邻的人需要1单位的开销。找一个方案，使得总开销最小。

算法：从左到右扫描
*/
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
  int n;
  while(cin >> n && n) {
    long long ans = 0, a, last = 0;
    for(int i = 0; i < n; i++) {
      cin >> a;
      ans += abs(last);
      last += a;
    }
    cout << ans << "\n";
  }
  return 0;
}
