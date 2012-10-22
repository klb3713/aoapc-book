// LA3942 Remember the Word
// Rujia Liu
#include<cstring>
#include<vector>
using namespace std;

const int maxnode = 4000 * 100 + 10;
const int sigma_size = 26;

// 字母表为全体小写字母的Trie
struct Trie {
  int ch[maxnode][sigma_size];
  int val[maxnode];
  int sz; // 结点总数
  void clear() { sz = 1; memset(ch[0], 0, sizeof(ch[0])); } // 初始时只有一个根结点
  int idx(char c) { return c - 'a'; } // 字符c的编号

  // 插入字符串s，附加信息为v。注意v必须非0，因为0代表“本结点不是单词结点”
  void insert(const char *s, int v) {
    int u = 0, n = strlen(s);
    for(int i = 0; i < n; i++) {
      int c = idx(s[i]);
      if(!ch[u][c]) { // 结点不存在
        memset(ch[sz], 0, sizeof(ch[sz]));
        val[sz] = 0;  // 中间结点的附加信息为0
        ch[u][c] = sz++; // 新建结点
      }
      u = ch[u][c]; // 往下走
    }
    val[u] = v; // 字符串的最后一个字符的附加信息为v
  }

  // 找字符串s的长度不超过len的前缀
  void find_prefixes(const char *s, int len, vector<int>& ans) {
    int u = 0;
    for(int i = 0; i < len; i++) {
      if(s[i] == '\0') break;
      int c = idx(s[i]);
      if(!ch[u][c]) break;
      u = ch[u][c];
      if(val[u] != 0) ans.push_back(val[u]); // 找到一个前缀
    }
  }
};

#include<cstdio>
const int maxl = 300000 + 10; // 文本串最大长度
const int maxw = 4000 + 10;   // 单词最大个数
const int maxwl = 100 + 10;   // 每个单词最大长度
const int MOD = 20071027;

int d[maxl], len[maxw], S;
char text[maxl], word[maxwl];
Trie trie;

int main() {
  int kase = 1;
  while(scanf("%s%d", text, &S) == 2) {
    trie.clear();
    for(int i = 1; i <= S; i++) {
      scanf("%s", word);
      len[i] = strlen(word);
      trie.insert(word, i);
    }
    memset(d, 0, sizeof(d));
    int L = strlen(text);
    d[L] = 1;
    for(int i = L-1; i >= 0; i--) {
      vector<int> p;
      trie.find_prefixes(text+i, L-i, p);
      for(int j = 0; j < p.size(); j++)
        d[i] = (d[i] + d[i+len[p[j]]]) % MOD;
    }
    printf("Case %d: %d\n", kase++, d[0]);
  }
  return 0;
}
