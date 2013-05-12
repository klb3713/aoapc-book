// UVa208 Firetruck
// Rujia Liu
// 题意：给一个无向图，输出从结点1到给定结点的所有路径，要求结点不能重复经过
// 算法：数据不难，直接回溯即可。但是需要注意两点：
// 1. 要事先判断路径是否存在，否则会超时
// 2. 必须按照字典序从小到大输出各路径。本程序的解决方法是给每个点的相邻点编号排序

#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn = 21 + 5;

int cnt, target, vis[maxn], route[maxn];
vector<int> G[maxn];

void dfs(int d, int u) {
  if(u == target) {
    for(int i = 0; i < d-1; i++) printf("%d ", route[i]);
    printf("%d\n", u);
    cnt++;
  } else for(int i = 0; i < G[u].size(); i++) {
    int v = G[u][i];
    if(!vis[v]) { vis[v] = 1; route[d] = v; dfs(d+1, G[u][i]); vis[v] = 0; }
  }
}

bool can_reach_target(int u) {
  if(u == target) return true;
  if(vis[u]) return false;
  vis[u] = true;
  for(int i = 0; i < G[u].size(); i++)
    if(can_reach_target(G[u][i])) return true;
  return false;
}

int main() {
  int kase = 0;
  while(scanf("%d", &target) == 1) {
    for(int i = 0; i < maxn; i++) G[i].clear();
    for(;;) {
      int x, y;
      scanf("%d%d", &x, &y);
      if(!x && !y) break;
      G[x].push_back(y);
      G[y].push_back(x);
    }
    for(int i = 0; i < maxn; i++) {
      if(!G[i].empty()) sort(G[i].begin(), G[i].end());
    }
    cnt = 0;
    printf("CASE %d:\n", ++kase);

    memset(vis, 0, sizeof(vis));
    if(can_reach_target(1)) {
      memset(vis, 0, sizeof(vis));
      route[0] = vis[1] = 1;
      dfs(1, 1);
    }
    printf("There are %d routes from the firestation to streetcorner %d.\n", cnt, target);
  }
  return 0;
}
