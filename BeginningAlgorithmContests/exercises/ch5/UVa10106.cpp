// UVa10106 Product
// Rujia Liu
// 题意：输入两个正整数X, Y（0<=X,Y<10^250）, 求X*Y
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

const int maxn = 1000;
struct bign{
  int len, s[maxn];

  bign() {
    memset(s, 0, sizeof(s));
    len = 1;
  }

  bign(int num) {
    *this = num;
  }

  bign(const char* num) {
    *this = num;
  }

  bign operator = (int num) {
    char s[maxn];
    sprintf(s, "%d", num);
    *this = s;
    return *this;
  }

  bign operator = (const char* num) {
    len = strlen(num);
    for(int i = 0; i < len; i++) s[i] = num[len-i-1] - '0';
    return *this;
  }

  string str() const {
    string res = "";
    for(int i = 0; i < len; i++) res = (char)(s[i] + '0') + res;
    if(res == "") res = "0";
    return res;
  }

  void clean() {
    while(len > 1 && !s[len-1]) len--;
  }

  bign operator * (const bign& b) {
    bign c; c.len = len + b.len;
    for(int i = 0; i < len; i++)
      for(int j = 0; j < b.len; j++)
        c.s[i+j] += s[i] * b.s[j];
    for(int i = 0; i < c.len-1; i++){
      c.s[i+1] += c.s[i] / 10;
      c.s[i] %= 10;
    }
    c.clean();
    return c;
  }
};

istream& operator >> (istream &in, bign& x) {
  string s;
  in >> s;
  x = s.c_str();
  return in;
}

ostream& operator << (ostream &out, const bign& x) {
  out << x.str();
  return out;
}

int main() {
  bign a, b;
  while(cin >> a >> b) cout << a * b << "\n";
  return 0;
}

