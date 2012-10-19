// LA4119 Always an Integer （限于篇幅，书上无此代码）
// Rujia Liu
#include<cstdio>
#include<cstdlib>
#include<cctype>
#include<string>
#include<vector>
#include<iostream>
#include<cassert>
using namespace std;

struct Polynomial {
  vector<int> a, p; // 第i项为a[i] * n^p[i]
  void parse_polynomial(string expr) { // 解析多项式（不带括号）
    int i = 0, len = expr.size();
    while(i < len) { // 每次循环体解析一个a*n^p
      int sign = 1;
      if(expr[i] == '+') i++;
      if(expr[i] == '-') { sign = -1; i++; }
      int v = 0;
      while(i < len && isdigit(expr[i])) v = v * 10 + expr[i++] - '0'; // 系数的绝对值
      if(i == len) { a.push_back(v); p.push_back(0); } // 常数项
      else {
        assert(expr[i] == 'n');
        if(v == 0) v = 1; // 无系数，按1处理
        v *= sign;
        if(expr[++i] == '^') { // 有指数项
          a.push_back(v);
          v = 0; // 清空v，接下来用v保存指数
          i++;
          while(i < len && isdigit(expr[i])) v = v * 10 + expr[i++] - '0';
          p.push_back(v);
        } else { // 无指数项
          a.push_back(v); p.push_back(1);
        }
      }
    }
  }

  // 计算f(x)除以MOD的余数
  int mod(int x, int MOD) {
    int n = a.size();
    int ans = 0;
    for(int i = 0; i < n; i++) {
      int m = a[i];
      for(int j = 0; j < p[i]; j++) m = (long long)m * x % MOD; // 注意避免溢出
      ans = ((long long)ans + m) % MOD; // 加法也可能会溢出！
    }
    return ans;
  }
};

bool check(string expr) {
  int p = expr.find('/');
  Polynomial poly;
  poly.parse_polynomial(expr.substr(1, p-2));
  int D = atoi(expr.substr(p+1).c_str());
  for(int i = 1; i <= poly.p[0]+1; i++)
    if(poly.mod(i, D) != 0) return false;
  return true;
}

int main() {
  int kase = 1;
  string expr;
  while(cin >> expr) {
    if(expr[0] == '.') break;
    printf("Case %d: ", kase++);
    if(check(expr)) printf("Always an integer\n");
    else printf("Not always an integer\n");
  }
  return 0;
}
