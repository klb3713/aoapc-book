// UVa673 Parentheses Balance
// Rujia Liu
// 题意：输入一个包含()和[]的括号序列，判断是否合法。
// 具体递归定义如下：1.空串合法；2.如果A和B都合法，则AB合法；3.如果A合法则(A)和[A]都合法。
// 算法：用一个栈。注意输入可能有空串
#include<iostream>
#include<stack>
#include<string>
using namespace std;

bool judge(const string& input) {
  int n = input.length();
  stack<char> s;
  for(int i = 0; i < n; i++) {
    char c = input[i];
    if(c == '(' || c == '[') s.push(c);
    else {
      if(s.empty()) return false;
      if(c == ')' && s.top() != '(') return false;
      if(c == ']' && s.top() != '[') return false;
      s.pop();
    }
  }
  return s.empty();
}

int main() {
  int T;
  string s;
  cin >> T;
  getline(cin, s); // 吃掉T后面的回车
  while(T--) {
    getline(cin, s);
    if(judge(s)) cout << "Yes\n"; else cout << "No\n";
  }
  return 0;
}
