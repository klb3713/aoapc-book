// UVa10391 Compound Words
// Rujia Liu
// 题意：给一个单词集合S，其中有多少个单词w可以写成a+b，其中a, b都是S里的单词？输入按字典序排列，输出也应按字典序排列
// 算法：逐个判断每个单词是否满足条件。判断方法是枚举a的长度
#include<iostream>
#include<set>
#include<vector>
using namespace std;

set<string> dict;

int main() {
  string s;
  while(cin >> s) dict.insert(s);
  for(set<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
    const string& w = *it;
    for(int p = 1; p < w.size(); p++)
      if(dict.count(w.substr(0, p)) && dict.count(w.substr(p, w.length()-p))) { cout << w << "\n"; break; }
  }    
  return 0;
}
