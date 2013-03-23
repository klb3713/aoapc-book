// UVa10054 The Necklace
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int maxcolor = 50;
int n, G[maxcolor+1][maxcolor+1], deg[maxcolor+1];

struct Edge {
  int from, to;
  Edge(int from, int to):from(from),to(to) {}
};

vector<Edge> ans;
void euler(int u){
  for(int v = 1; v <= maxcolor; v++) if(G[u][v]) {
    G[u][v]--; G[v][u]--;
    euler(v);
    ans.push_back(Edge(u, v));
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%d", &n);
    memset(G, 0, sizeof(G));
    memset(deg, 0, sizeof(deg));
    int start = -1;
    for(int i = 0; i < n; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      G[u][v]++; G[v][u]++;
      deg[u]++; deg[v]++;
      start = u;
    }

    // 无向图的欧拉回路
    bool solved = true;
    for(int i = 1; i <= maxcolor; i++)
      if(deg[i] % 2 == 1) { solved = false; break; } // 检查度数
    if(solved) {
      ans.clear();
      euler(start);
      if(ans.size() != n || ans[0].to != ans[ans.size()-1].from) solved = false;
    }

    printf("Case #%d\n", kase);
    if(!solved)
      printf("some beads may be lost\n");
    else
      for(int i = ans.size()-1; i >= 0; i--) printf("%d %d\n", ans[i].from, ans[i].to);

    if(kase < T) printf("\n");
  }
  return 0;
}
