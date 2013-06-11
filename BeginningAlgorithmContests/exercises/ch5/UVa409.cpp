// UVa409 Excuses, Excuses!
// Rujia Liu
// 题意：输入k个关键字和e行文本，找出所有包含最多关键字的文本行。
// 细节：字母不区分大小写；连续字母串算一个单词（前后不一定是空格，可能是其他非字母字符）；同一个关键字出现多次按多次算

#include<iostream>
#include<cstdio>
#include<string>
#include<set>
#include<sstream>
using namespace std;

const int maxn = 100;
int k, e, cnt[maxn];
set<string> keywords;
string excuses[maxn];

int count(const string& s) {
  string buf = s, token;
  for(int i = 0; i < buf.size(); i++)
    if(isalpha(buf[i])) buf[i] = tolower(buf[i]); else buf[i] = ' ';
  stringstream ss(buf);
  int cnt = 0;
  while(ss >> token) {
    if(keywords.count(token)) cnt++;
  }
  return cnt;
}

int main() {
  string s;
  int kase = 0;
  while(getline(cin, s)) {
    sscanf(s.c_str(), "%d%d", &k, &e);
    keywords.clear();
    for(int i = 0; i < k; i++) {
      getline(cin, s);
      keywords.insert(s);
    }
    int worst = 0;
    for(int i = 0; i < e; i++) {
      getline(cin, excuses[i]);
      cnt[i] = count(excuses[i]);
      if(cnt[i] > worst) worst = cnt[i];
    }

    printf("Excuse Set #%d\n", ++kase);
    for(int i = 0; i < e; i++) if(cnt[i] == worst)
      printf("%s\n", excuses[i].c_str());
    printf("\n");
  }
  return 0;
}
