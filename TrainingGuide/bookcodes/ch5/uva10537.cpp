// UVa10537 Toll! Revisited
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 52 + 10;
const long long INF = 1LL << 60;
typedef long long LL;

int n, G[maxn][maxn], src, dest, p;
int mark[maxn]; // 标记
LL d[maxn];     // d[i]表示从点i出发（已经交过点i的税了）时至少要带多少东西，到dest时还能剩p个东西

int read_node() {
  char ch[9];
  scanf("%s", ch);
  if(ch[0] >= 'A' && ch[0] <= 'Z') return ch[0] - 'A';
  else return ch[0] - 'a' + 26;
}

char format_node(int u) {
  return u < 26 ? 'A' + u : 'a' + (u - 26);
}

// 拿着item个东西去结点next，还剩多少个东西
LL forward(LL item, int next) {
  if(next < 26) return item - (item + 19) / 20;
  return item - 1;
}

// 至少要拿着多少个东西到达结点u，交税以后还能剩d[u]个东西
// 为了使代码容易理解，这里使用一种不太数学的解法
LL back(int u) {
  if(u >= 26) return d[u]+1;
  LL X = d[u] * 20 / 19; // 初始值
  while(forward(X, u) < d[u]) X++; // 调整
  return X;
}

void solve() {
  n = 52; // 总是有52个结点
  memset(mark, 0, sizeof(mark));
  d[dest] = p;
  mark[dest] = 1;
  for(int i = 0; i < n; i++) if(i != dest) {
    d[i] = INF;
    if(G[i][dest]) d[i] = back(dest);
  }

  // Dijkstra主过程，逆推
  while(!mark[src]) {
    // 找最小的d
    int minu = -1;
    for(int i = 0; i < n; i++) if(!mark[i]) {
      if(minu < 0 || d[i] < d[minu]) minu = i;
    }
    mark[minu] = 1;
    // 更新其他结点的d
    for(int i = 0; i < n; i++) if(!mark[i]) {
      if(G[i][minu]) d[i] = min(d[i], back(minu));
    }
  }

  // 输出
  printf("%lld\n", d[src]);
  printf("%c", format_node(src));
  int u = src;
  LL item = d[src];
  while(u != dest) {
    int next;
    for(next = 0; next < n; next++) // 找到第一个可以走的结点
      if(G[u][next] && forward(item, next) >= d[next]) break;
    item = d[next];
    printf("-%c", format_node(next));
    u = next;
  }
  printf("\n");
}

int main() {
  int kase = 0;
  while(scanf("%d", &n) == 1 && n >= 0) {
    memset(G, 0, sizeof(G));
    for(int i = 0; i < n; i++) {
      int u = read_node();
      int v = read_node();
      if(u != v) G[u][v] = G[v][u] = 1;
    }
    scanf("%d", &p);
    src = read_node();
    dest = read_node();
    printf("Case %d:\n", ++kase);
    solve();
  }
  return 0;
}
