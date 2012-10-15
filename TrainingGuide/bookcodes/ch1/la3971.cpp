// LA3971 Assemble
// Rujia Liu
#include<cstdio>
#include<string>
#include<vector>
#include<map>
using namespace std;

int cnt; // 组件的类型数
map<string,int> id;
int ID(string s) {
  if(!id.count(s)) id[s] = cnt++;
  return id[s];
}

const int maxn = 1000 + 5;

struct Component {
  int price;
  int quality;
};
int n, b; // 组件的数目，预算
vector<Component> comp[maxn];

// 品质因子不小于q的组件能否组装成一个不超过b元的电脑
bool ok(int q) {
  int sum = 0;
  for(int i = 0; i < cnt; i++) {
    int cheapest = b+1, m = comp[i].size();
    for(int j = 0; j < m; j++)
      if(comp[i][j].quality >= q) cheapest = min(cheapest, comp[i][j].price);
    if(cheapest == b+1) return false;
    sum += cheapest;
    if(sum > b) return false;
  }
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &n, &b);

    cnt = 0;
    for(int i = 0; i < n; i++) comp[i].clear();
    id.clear();

    int maxq = 0;
    for(int i = 0; i < n; i++) {
      char type[30], name[30];
      int p, q;
      scanf("%s%s%d%d", type, name, &p, &q);
      maxq = max(maxq, q);
      comp[ID(type)].push_back((Component){p, q});
    }

    int L = 0, R = maxq;
    while(L < R) {
      int M = L + (R-L+1)/2;
      if(ok(M)) L = M; else R = M-1;
    }
    printf("%d\n", L);
  }
  return 0;
}
