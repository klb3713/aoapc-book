// UVa10183 How many Fibs?
// Rujia Liu
// 题意：输入大整数a, b, 求[a,b]里有多少个fibonacci数
// 算法：预处理，然后直接判断
#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
using namespace std;

struct BigInteger {
  static const int BASE = 100000000;
  static const int WIDTH = 8;
  vector<int> s;

  BigInteger(int num=0) { *this = num; }
  BigInteger operator = (int num) { s.clear(); s.push_back(num); return *this; }
  BigInteger operator = (string str) {
    s.clear();
    int x, len = (str.length() - 1) / WIDTH + 1;
    for(int i = 0; i < len; i++) {
      int end = str.length() - i*WIDTH;
      int start = max(0, end - WIDTH);
      sscanf(str.substr(start, end-start).c_str(), "%d", &x);
      s.push_back(x);
    }
    return *this;
  }

  bool operator == (const BigInteger& b) const {
    return s == b.s;
  }

  bool operator < (const BigInteger& b) const {
    if(s.size() != b.s.size()) return s.size() < b.s.size();
    for(int i = s.size()-1; i >= 0; i--)
      if(s[i] != b.s[i]) return s[i] < b.s[i];
    return false; // 相等
  }

  bool operator <= (const BigInteger& b) const {
    return !(b < *this);
  }

  BigInteger operator + (const BigInteger& b) const {
    BigInteger c;
    c.s.clear();
    for(int i = 0, g = 0; ; i++) {
      if(g == 0 && i >= s.size() && i >= b.s.size()) break;
      int x = g;
      if(i < s.size()) x += s[i];
      if(i < b.s.size()) x += b.s[i];
      c.s.push_back(x % BASE);
      g = x / BASE;
    }
    return c;
  }
};

istream& operator >> (istream &in, BigInteger& x) {
  string s;
  if(!(in >> s)) return in;
  x = s;
  return in;
}

const int maxn = 600;
BigInteger f[maxn+1];

int main() {
  f[1] = 1;
  f[2] = 2;
  for(int i = 3; i <= maxn; i++)
    f[i] = f[i-1] + f[i-2];

  BigInteger a, b;
  while(cin >> a >> b) {
    if(a == 0 && b == 0) break;
    int cnt = 0;
    for(int i = 1; i <= maxn; i++)
      if(a <= f[i] && f[i] <= b) cnt++;
    cout << cnt << "\n";
  }
  return 0;
}
