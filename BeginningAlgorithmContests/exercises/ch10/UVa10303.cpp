// UVa10303 How Many Trees?
// Rujia Liu
// 题意：求n元素排序二叉树的个数
// 算法：就是Catalan数（从C[0]开始），即：1, 1, 2, 5, 14, ... C[n+1] = C[n] * (4n+2)/(n+2)
#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct BigInteger {
  static const int BASE = 100000000;
  static const int WIDTH = 8;
  vector<int> s;

  BigInteger(long long num = 0) { *this = num; }
  BigInteger operator = (long long num) {
    s.clear();
    do {
      s.push_back(num % BASE);
      num /= BASE;
    } while(num > 0);
    return *this;
  }
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

  BigInteger divmod (int b, int& d) const {
    BigInteger c;
    c.s.clear();
    d = 0;
    for(int i = s.size()-1; i >= 0; i--) {
      long long v = (long long)d * BASE + s[i];
      c.s.push_back(v / b);
      d = v % b;
    }
    reverse(c.s.begin(), c.s.end());
    c.adjust();
    return c;
  }

  BigInteger operator / (int b) const {
    int d;
    return this->divmod(b, d);
  }

  BigInteger operator % (int b) const {
    int d;
    this->divmod(b, d);
    return d;
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

const int maxn = 1000 + 5;

BigInteger C[maxn+1];

int main() {
  C[0] = 1;
  for(int i = 0; i < maxn; i++)
    C[i+1] = C[i] * (i*4+2) / (i+2);
  int n;
  while(cin >> n && n) cout << C[n] << "\n";
  return 0;
}
