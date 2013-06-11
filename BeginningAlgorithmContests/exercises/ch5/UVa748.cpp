// UVa748 Exponentiation
// Rujia Liu
// 题意：求R^n，其中R是一个不超过100的小数，最多有6位。0<n<=25。不能输出多余的0

#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

const int maxn = 200;
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

  bign operator *= (const bign& b) {
    *this = *this * b;
    return *this;
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

#include<cmath>

int main() {
  double r;
  int n;
  while(cin >> r >> n) {
    // 设r = p / 10^q
    int q = 0;
    while(fabs(r - floor(r+0.5)) > 1e-6) { q++; r*=10; }
    int p = floor(r+0.5);

    bign a = 1;
    for(int i = 0; i < n; i++) a *= p; // 求p^n

    // 输出a / 10^(qn)
    string s = a.str();
    int left = s.length() - q*n;
    for(int i = 0; i < left; i++) cout << s[i];
    cout << ".";
    for(int i = 0; i < q*n-(int)s.length(); i++) cout << "0";
    for(int i = max(0, left); i < (int)s.length(); i++) cout << s[i];
    cout << "\n";
  }
  return 0;
}
