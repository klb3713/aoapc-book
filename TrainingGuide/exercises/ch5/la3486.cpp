// LA3486 Cells
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;

const int maxn = 300000 + 5;
const int maxtot = 20000000 + 5;
int n, c[maxn], start[maxn];
int pre[maxtot], post[maxtot];

// 非递归dfs。由于没有使用耗时的memset操作，在结点入栈之前需设置pre=0
void dfs(int root) {
  stack<int> st;
  pre[root] = 0; 
  st.push(root);
  int dfs_clock = 1;
  while(!st.empty()) {
    int u = st.top();
    if(pre[u]) { // 结点u处理完毕
      post[u] = dfs_clock++;
      st.pop();
      continue;
    }
    pre[u] = dfs_clock++; // 结点u开始处理
    for(int i = start[u]; i < start[u] + c[u]; i++) {
      if(i < n) { pre[i] = 0; st.push(i); }
      else { pre[i] = dfs_clock++; post[i] = dfs_clock++; } // 叶结点不用入栈，直接计算pre和post
    }
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    printf("Case %d:\n", kase);

    int q, a, b;
    scanf("%d", &n);
    int s = 1;
    for(int i = 0; i < n; i++) { scanf("%d", &c[i]); start[i] = s; s += c[i]; }
    dfs(0);

    scanf("%d", &q);
    while(q--) {
      scanf("%d%d", &a, &b);
      if(pre[a] < pre[b] && post[a] > post[b]) printf("Yes\n"); else printf("No\n");
    }
    if(kase < T) printf("\n");
  }
  return 0;
}
