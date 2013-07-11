// UVa10516 Another Counting Problem
// Rujia Liu
// 题意：输入n, d，统计深度为d（即叶子深度最大值为d。根的深度为0）的严格n叉树（即每个非叶结点都有n个儿子）的个数。
// 算法：给定n，设深度不超过d的树的个数为f[d]，则答案为f[d]-f[d-1]。
// 深度不超过d的树要么就是一个单结点，要么每个子树都是深度不超过d-1的，因此f[d]=f[d-1]^n+1
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

  BigInteger operator *= (const BigInteger& b) { *this = *this * b; return *this; }
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

const int maxn = 32;

BigInteger f[maxn+1];

int main() {
  int n, d;
  while(cin >> n >> d && n) {
    cout << n << " " << d << " ";
    if(d == 0) cout << "1\n";
    else {
      f[0] = 1;
      for(int i = 1; i <= d; i++) {
        f[i] = 1;
        for(int j = 0; j < n; j++) f[i] *= f[i-1];
        f[i] += 1;
      }
      cout << f[d]-f[d-1] << "\n";
    }
  }
  return 0;
}
