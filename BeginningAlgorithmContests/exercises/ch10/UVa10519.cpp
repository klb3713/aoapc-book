// UVa10519 !! REALLY STRANGE !!
// Rujia Liu
// 题意：平面上n个圆最多把平面分成多少个部分？比如n=2时答案为4
// 算法：n=1, 2, 3, 4时答案为2, 4, 8, 14，增量为2, 4, 6...
// 因此f(n) = 2 + 2 + 4 + 6 + 8 + ... + 可以得到f(n)=n(n-1)+2
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

  BigInteger operator += (const BigInteger& b) { *this = *this + b; return *this; }

  void adjust() {
    while(s.size() > 1 && s.back() == 0) s.pop_back();
  }

  BigInteger operator - (const BigInteger& b) const {
    BigInteger c;
    c.s.resize(s.size());
    for(int i = 0, g = 0; i < s.size(); i++) {
      c.s[i] = s[i] - g;
      g = 0;
      int sub = (i < b.s.size() ? b.s[i] : 0);
      if(c.s[i] < sub) { g = 1; c.s[i] += BASE; }
      c.s[i] -= sub;
    }
    c.adjust();
    return c;
  }

  BigInteger operator * (const BigInteger& b) const {
    BigInteger c;
    c.s.resize(s.size() + b.s.size() + 1);
    fill(c.s.begin(), c.s.end(), 0);
    for(int i = 0; i < s.size(); i++)
      for(int j = 0; j < b.s.size(); j++) {
        long long sum = (long long)s[i] * b.s[j] + c.s[i+j];
        c.s[i+j+1] += sum / BASE;
        c.s[i+j] = sum % BASE;
      }
    c.adjust();
    return c;
  }
};

ostream& operator << (ostream &out, const BigInteger& x) {
  out << x.s.back();
  for(int i = x.s.size()-2; i >= 0; i--) {
    char buf[20];
    sprintf(buf, "%08d", x.s[i]);
    for(int j = 0; j < strlen(buf); j++) out << buf[j];
  }
  return out;
}

istream& operator >> (istream &in, BigInteger& x) {
  string s;
  if(!(in >> s)) return in;
  x = s;
  return in;
}

const int maxn = 10000 + 5;

int main() {
  BigInteger n;
  while(cin >> n) {
    if(n == 0) cout << "1\n";
    else cout << n*(n-1)+2 << "\n";
  }
  return 0;
}
