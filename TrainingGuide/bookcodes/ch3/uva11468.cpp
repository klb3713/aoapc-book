// UVa11468 Substring
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<queue>
#include<cstdio>
#include<map>
#include<string>
using namespace std;

const int SIGMA_SIZE = 64;
const int MAXNODE = 500; // 结点总数
const int MAXS = 20 + 10; // 模板个数

int idx[256], n;
double prob[SIGMA_SIZE];

struct AhoCorasickAutomata {
  int ch[MAXNODE][SIGMA_SIZE];
  int f[MAXNODE];    // fail函数
  int match[MAXNODE];  // 是否包含某一个字符串
  int sz;            // 结点总数

  void init() {
    sz = 1;
    memset(ch[0], 0, sizeof(ch[0]));
  }

  // 插入字符串
  void insert(char *s) {
    int u = 0, n = strlen(s);
    for(int i = 0; i < n; i++) {
      int c = idx[s[i]];
      if(!ch[u][c]) {
        memset(ch[sz], 0, sizeof(ch[sz]));
        match[sz] = 0;
        ch[u][c] = sz++;
      }
      u = ch[u][c];
    }
    match[u] = 1;
  }

  // 计算fail函数
  void getFail() {
    queue<int> q;
    f[0] = 0;
    // 初始化队列
    for(int c = 0; c < SIGMA_SIZE; c++) {
      int u = ch[0][c];
      if(u) { f[u] = 0; q.push(u); }
    }
    // 按BFS顺序计算fail
    while(!q.empty()) {
      int r = q.front(); q.pop();
      for(int c = 0; c < SIGMA_SIZE; c++) {
        int u = ch[r][c];
        if(!u) { ch[r][c] = ch[f[r]][c]; continue; }
        q.push(u);
        int v = f[r];
        while(v && !ch[v][c]) v = f[v];
        f[u] = ch[v][c];
        match[u] |= match[f[u]];
      }
    }
  }

  void dump() {
    printf("sz = %d\n", sz);
    for(int i = 0; i < sz; i++) printf("%d: %d %d %d\n", i, ch[i][0], ch[i][1], match[i]);
    printf("\n");
  }

};

AhoCorasickAutomata ac;

double d[MAXNODE][105];
int vis[MAXNODE][105];
double getProb(int u, int L) {
  if(!L) return 1.0;
  if(vis[u][L]) return d[u][L];
  vis[u][L] = 1;
  double &ans = d[u][L];
  ans = 0.0;
  for(int i = 0; i < n; i++)
    if(!ac.match[ac.ch[u][i]]) ans += prob[i] * getProb(ac.ch[u][i], L-1);
  return ans;
}

char s[30][30];

int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    int k, L;
    scanf("%d", &k);
    for(int i = 0; i < k; i++) scanf("%s", s[i]);
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
      char ch[9];
      scanf("%s%lf", ch, &prob[i]);
      idx[ch[0]] = i;
    }
    ac.init();
    for(int i = 0; i < k; i++) ac.insert(s[i]);
    ac.getFail();
    scanf("%d", &L);
    memset(vis, 0, sizeof(vis));
    printf("Case #%d: %.6lf\n", kase, getProb(0, L));
  }
  return 0;
}
