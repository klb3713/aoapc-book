// UVa11991 Easy Problem from Rujia Liu
// Rujia Liu
#include<cstdio>
#include<vector>
#include<map>
using namespace std;

map<int, vector<int> > a; // 最后两个>不要连写，否则会被误认为>>

int main() {
  int n, m, x, y;
  while(scanf("%d%d", &n, &m) == 2) {
    a.clear();
    for(int i = 0; i < n; i++) {
      scanf("%d", &x); if(!a.count(x)) a[x] = vector<int>();
      a[x].push_back(i+1);
    }
    while(m--) {
      scanf("%d%d", &x, &y);
      if(!a.count(y) || a[y].size() < x) printf("0\n");
      else printf("%d\n", a[y][x-1]);
    }
  }
  return 0;
}
