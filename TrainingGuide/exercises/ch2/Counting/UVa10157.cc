// UVa10157 Expressions
// 陈锋
#include<cstring>
#include<string>
#include<cstdio>
#include<cmath>
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

const int MAX = 150;
typedef bign<100> longInt;
longInt f[MAX + 10][MAX + 10];

int main() {
    int n, d;
    for(int j = 0; j <= MAX; j++)
        f[0][j] = 1;
    
    for(int i = 1; i <= MAX; i++)
        for(int j = 0; j <= MAX; j++)
        {
            longInt& ans = f[i][j];
            ans = 0;
            for(int k = 0; k < i; k++)
                ans += f[k][j-1] * f[i-k-1][j];
        }
    /*
    我们可以把最左边的“(”和其配对的“)”看成一组分界线，它们把剩余的括号分成了内外两部分，
    其中里面的部分深度最多为d-1，外面部分的深度最多为d。f[i][j]表示一共有i对括号时深度不超过j的表达式的数量，
    那么f[i][j]=sum{f[k][j-1]*f[i-k-1][j]}，最后输出的结果即是f[n/2][d]-f[n/2][d-1]，当然前提是n为偶数。
    边界条件是，i = 0时，f = 1
    */
    
    while(scanf("%d%d", &n, &d) == 2)
    {
        if(n % 2) puts("0");
        else  
        {
            const longInt& result = f[n/2][d] - f[n/2][d-1];
            puts(result.str().c_str());
        }
    }
    return 0;
}