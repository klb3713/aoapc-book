// UVa10340 All in All
// Rujia Liu
// 题意：输入两个字符串S和T，判断S是否为T的（不一定连续的）子串
#include<iostream>
#include<string>
using namespace std;

int main() {
  string s, t;
  while(cin >> s >> t) {
    int n = s.length(), m = t.length();
    bool ok = true;
    int i, j;
    for(i = j = 0; i < n; i++, j++) {
      while(j < m && t[j] != s[i]) j++;
      if(j == m) { ok = false; break; }
    }
    if(ok) cout << "Yes\n"; else cout << "No\n";
  }
  return 0;
}

