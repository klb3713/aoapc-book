// UVa10763 Foreign Exchange
// Rujia Liu
// 题意：有n个学生想交换。用(a,b)表示一个想从国家a交换到国家b的学生。是否可以讲学生两两配对使得配对的两个学生形如(a,b)和(b,a)？
#include<cstdio>
#include<map>
#include<algorithm>
using namespace std;

int main() {
  int n, a, b;
  while(scanf("%d", &n) == 1 && n) {
    map<pair<int,int>, int> cnt;
    for(int i = 0; i < n; i++) {
      scanf("%d%d", &a, &b);
      int v = 1;
      if(a > b) { swap(a, b); v = -1; }
      pair<int,int> p = make_pair(a, b);
      if(!cnt.count(p)) cnt[p] = v;
      else cnt[p] += v;
    }
    bool ok = true;
    for(map<pair<int,int>, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
      if(it->second != 0) { ok = false; break; }
    }
    if(ok) printf("YES\n"); else printf("NO\n");
  }
  return 0;
}
