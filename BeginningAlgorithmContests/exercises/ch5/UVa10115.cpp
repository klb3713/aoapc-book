// UVa10115 Automatic Editing
// Rujia Liu
// 题意：输入n次替换，每次替换用两个字符串s1, s2表示（各占一行，s2可能为空串），即把第一个遇到的s1替换为s2。如果替换成功那么再替换一次，直到
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
const int maxn = 20;
string s1[maxn], s2[maxn], s;

int main() {
  while(getline(cin, s)) {
    int n;
    sscanf(s.c_str(), "%d", &n);
    if(!n) break;
    for(int i = 0; i < n; i++) {
      getline(cin, s1[i]);
      getline(cin, s2[i]);
    }
    getline(cin, s);
    for(int i = 0; i < n; i++) {
      for(;;) {
        int p = s.find(s1[i]);
        if(p < 0) break;
        s = s.substr(0, p) + s2[i] + s.substr(p + s1[i].length());
      }
    }
    cout << s << "\n";
  }
  return 0;
}
