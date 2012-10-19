// LA4670 Dominating Patterns
// Rujia Liu
#include<cstring>
#include<queue>
#include<cstdio>
#include<map>
#include<string>
using namespace std;

const int SIGMA_SIZE = 26;
const int MAXNODE = 11000;
const int MAXS = 150 + 10;

map<string,int> ms;

struct AhoCorasickAutomata {
  int ch[MAXNODE][SIGMA_SIZE];
  int f[MAXNODE];    // fail函数
  int val[MAXNODE];  // 每个字符串的结尾结点都有一个非0的val
  int last[MAXNODE]; // 输出链表的下一个结点
  int cnt[MAXS];
  int sz;

  void init() {
    sz = 1;
    memset(ch[0], 0, sizeof(ch[0]));
    memset(cnt, 0, sizeof(cnt));
    ms.clear();
  }

  // 字符c的编号
  int idx(char c) {
    return c-'a';
  }

  // 插入字符串。v必须非0
  void insert(char *s, int v) {
    int u = 0, n = strlen(s);
    for(int i = 0; i < n; i++) {
      int c = idx(s[i]);
      if(!ch[u][c]) {
        memset(ch[sz], 0, sizeof(ch[sz]));
        val[sz] = 0;
        ch[u][c] = sz++;
      }
      u = ch[u][c];
    }
    val[u] = v;
    ms[string(s)] = v;
  }

  // 递归打印以结点j结尾的所有字符串
  void print(int j) {
    if(j) {
      cnt[val[j]]++;
      print(last[j]);
    }
  }

  // 在T中找模板
  int find(char* T) {
    int n = strlen(T);
    int j = 0; // 当前结点编号，初始为根结点
    for(int i = 0; i < n; i++) { // 文本串当前指针
      int c = idx(T[i]);
      while(j && !ch[j][c]) j = f[j]; // 顺着细边走，直到可以匹配
      j = ch[j][c];
      if(val[j]) print(j);
      else if(last[j]) print(last[j]); // 找到了！
    }
  }

  // 计算fail函数
  void getFail() {
    queue<int> q;
    f[0] = 0;
    // 初始化队列
    for(int c = 0; c < SIGMA_SIZE; c++) {
      int u = ch[0][c];
      if(u) { f[u] = 0; q.push(u); last[u] = 0; }
    }
    // 按BFS顺序计算fail
    while(!q.empty()) {
      int r = q.front(); q.pop();
      for(int c = 0; c < SIGMA_SIZE; c++) {
        int u = ch[r][c];
        if(!u) continue;
        q.push(u);
        int v = f[r];
        while(v && !ch[v][c]) v = f[v];
        f[u] = ch[v][c];
        last[u] = val[f[u]] ? f[u] : last[f[u]];
      }
    }
  }

};

AhoCorasickAutomata ac;
char text[1000001], P[151][80];
int n, T;

int main() {
  while(scanf("%d", &n) == 1 && n) {
    ac.init();
    for(int i = 1; i <= n; i++) {
      scanf("%s", P[i]);
      ac.insert(P[i], i);
    }
    ac.getFail();
    scanf("%s", text);
    ac.find(text);
    int best =  -1;
    for(int i = 1; i <= n; i++)
      if(ac.cnt[i] > best) best = ac.cnt[i];
    printf("%d\n", best);
    for(int i = 1; i <= n; i++)
      if(ac.cnt[ms[string(P[i])]] == best) printf("%s\n", P[i]);
  }
  return 0;
}
