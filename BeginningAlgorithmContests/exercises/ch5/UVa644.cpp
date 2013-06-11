// UVa644 Immediate Decodability
// Rujia Liu
// 题意：给一个01字符串集合，判断是否其中一个串是另一个的前缀

#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<string> codes;

bool read() {
  codes.clear();
  string s;
  for(;;) {
    if(!(cin >> s)) return false;
    if(s[0] == '9') return true;
    codes.push_back(s);
  }
}

bool solve() {
  int n = codes.size();
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      if(i != j && codes[i].find(codes[j]) == 0) return false;
  return true;
}

int main() {
  int kase = 0;
  while(read()) {
    bool b = solve();
    cout << "Set " << ++kase << " is ";
    if(!b) cout << "not ";
    cout << "immediately decodable\n";
  }
  return 0;
}
