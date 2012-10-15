// UVa10859 Placing Lampposts
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

vector<int> adj[1010]; // 森林是稀疏的，这样保存省空间，枚举相邻结点也更快
int vis[1010][2], d[1010][2], n, m;

int dp(int i, int j, int f) {
  // 在DFS的同时进行动态规划，f是i的父结点，它不存入状态里
  if(vis[i][j]) return d[i][j];
  vis[i][j] = 1;
  int& ans = d[i][j];

  // 放灯总是合法决策
  ans = 2000; // 灯的数量加1，x加2000
  for(int k = 0; k < adj[i].size(); k++)
    if(adj[i][k] != f) // 这个判断非常重要！除了父结点之外的相邻结点才是子结点
      ans += dp(adj[i][k], 1, i); // 注意，这些结点的父结点是i
  if(!j && f >= 0) ans++; // 如果i不是根，且父结点没放灯，则x加1

  if(j || f < 0) { // i是根或者其父结点已放灯，i才可以不放灯
    int sum = 0;
    for(int k = 0; k < adj[i].size(); k++)
      if(adj[i][k] != f)
        sum += dp(adj[i][k], 0, i);
    if(f >= 0) sum++; // 如果i不是根，则x加1
    ans = min(ans, sum);
  }
  return ans;
}

int main() {
  int T, a, b;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) adj[i].clear();
    // adj里保存着上一组数据的值，必须清空
    for(int i = 0; i < m; i++) {
      scanf("%d%d", &a, &b);
      adj[a].push_back(b);
      adj[b].push_back(a); // 因为是无向图
    }
    memset(vis, 0, sizeof(vis));
    int ans = 0;
    for(int i = 0; i < n; i++)
      if(!vis[i][0]) // 新的一棵树
        ans += dp(i,0,-1); // i是树根，因此父结点不存在（-1）
    printf("%d %d %d\n", ans/2000, m-ans%2000, ans%2000); //从x计算3个整数
  }
  return 0;
}
