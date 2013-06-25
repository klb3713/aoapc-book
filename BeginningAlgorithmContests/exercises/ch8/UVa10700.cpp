// UVa10700 Camel trading
// Rujia Liu
// 题意：给一个包含1~12的整数、加号和乘号的表达式，随意加括号后计算，求所能得到的最大值和最小值
#include<string>
#include<sstream>
#include<iostream>
using namespace std;

long long calc(long long a, long long b, char op) {
  if(op == '+') return a + b;
  return a * b;
}

long long calc(const string& s, char op) {
  string s2 = s;
  for(int i = 0; i < s2.length(); i++)
    if(s2[i] == op) s2[i] = ' ';
  long long ans, v;
  stringstream ss(s2);
  ss >> ans;
  while(ss >> v) ans = calc(ans, v, op);
  return ans;
}

// 先算op1，再算op2
long long calc(const string& s, char op1, char op2) {
  string s2 = s;
  for(int i = 0; i < s2.length(); i++)
    if(s2[i] == op2) s2[i] = ' ';

  long long ans;
  stringstream ss(s2);
  string term;
  ss >> term;
  ans = calc(term, op1);
  while(ss >> term) ans = calc(ans, calc(term, op1), op2);
  return ans;
}

int main() {
  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    long long maxv = calc(s, '+', '*');
    long long minv = calc(s, '*', '+');
    cout << "The maximum and minimum are " << maxv << " and " << minv << ".\n";
  }
  return 0;
}

