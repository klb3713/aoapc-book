// UVa11375 Matches
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

template<int maxn>
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

  bign operator + (const bign& b) const{
    bign c;
    c.len = 0;
    for(int i = 0, g = 0; g || i < max(len, b.len); i++) {
      int x = g;
      if(i < len) x += s[i];
      if(i < b.len) x += b.s[i];
      c.s[c.len++] = x % 10;
      g = x / 10;
    }
    return c;
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

  bign operator - (const bign& b) {
    bign c; c.len = 0;
    for(int i = 0, g = 0; i < len; i++) {
      int x = s[i] - g;
      if(i < b.len) x -= b.s[i];
      if(x >= 0) g = 0;
      else {
        g = 1;
        x += 10;
      }
      c.s[c.len++] = x;
    }
    c.clean();
    return c;
  }

  bool operator < (const bign& b) const{
    if(len != b.len) return len < b.len;
    for(int i = len-1; i >= 0; i--)
      if(s[i] != b.s[i]) return s[i] < b.s[i];
    return false;
  }

  bool operator > (const bign& b) const{
    return b < *this;
  }

  bool operator <= (const bign& b) {
    return !(b > *this);
  }

  bool operator == (const bign& b) {
    return !(b < *this) && !(*this < b);
  }

  bign operator += (const bign& b) {
    *this = *this + b;
    return *this;
  }
};

typedef bign<500> LL;

const int c[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6}; // 各数字需要的火柴数量
const int MAXN = 2000;
const int SIZE = MAXN + 48;
LL d[SIZE], f[SIZE]; // 数组大小为2的幂时，效率会更高
int main() {
  memset(d, 0, sizeof(d)); // d[i]为恰好用i根火柴可以组成的正整数（不含0）
  d[0] = 1;
  for(int i = 0; i <= MAXN; i++)
    for(int j = 0; j < 10; j++)
      if(!(i==0&&j==0) && i+c[j] <= MAXN) d[i+c[j]] += d[i]; // i=j=0时不允许转移
  f[0] = 0;
  for(int i = 1; i <= MAXN; i++)
    f[i] = f[i-1] + d[i];
  for(int i = 1; i <= MAXN; i++)
    if(i >= 6) f[i] += 1; // n>=6时，可以组成“0”

  int n;
  while(scanf("%d", &n) == 1)
    printf("%s\n", f[n].str().c_str()); 
  return 0;
}
