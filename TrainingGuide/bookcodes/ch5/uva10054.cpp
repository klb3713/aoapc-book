// UVa10054 The Necklace
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int maxcolor = 50;
int n, G[maxcolor+1][maxcolor+1];

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
    int start = -1;
    for(int i = 0; i < n; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      G[u][v]++; G[v][u]++;
      start = u;
    }
    ans.clear();
    euler(start);
    printf("Case #%d\n", kase);
    if(ans.size() != n || ans[0].to != ans[ans.size()-1].from) printf("some beads may be lost\n");
    else for(int i = ans.size()-1; i >= 0; i--) printf("%d %d\n", ans[i].from, ans[i].to);

    if(kase < T) printf("\n");
  }
  return 0;
}
