// UVa537 Artificial Intelligence?
// Rujia Liu
// 题意：输入一段物理计算题文本，包含U=??V, I=??A, P=??W中的恰好两个，要求计算出第三个。公式为P=U*I。单位可能有m, k, M的前缀。
#include<iostream>
#include<cstdio>
#include<string>
using namespace std;

string s;

bool get(string sub, double& v) {
  int p = s.find(sub);
  if(p < 0) return false;
  p += 2;
  int q = p;
  while(isdigit(s[q]) || s[q] == '.') q++;
  sscanf(s.substr(p).c_str(), "%lf", &v);
  if(s[q] == 'm') v *= 1e-3;
  else if(s[q] == 'k') v *= 1e3;
  else if(s[q] == 'M') v *= 1e6;
  return true;
}

int main() {
  int T;
  getline(cin, s);
  sscanf(s.c_str(), "%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    getline(cin, s);
    printf("Problem #%d\n", kase);
    double P, I, U;
    bool bP = get("P=", P);
    bool bI = get("I=", I);
    bool bU = get("U=", U);
    if(!bP) printf("P=%.2lfW\n\n", U*I);
    else if(!bI) printf("I=%.2lfA\n\n", P/U);
    else printf("U=%.2lfV\n\n", P/I);
  }
  return 0;
}
