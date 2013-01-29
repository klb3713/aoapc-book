// UVa11732 strcmp() Anyone?
// Rujia Liu
#include<cstring>
#include<vector>
using namespace std;

const int maxnode = 4000 * 1000 + 10;
const int sigma_size = 26;

// 字母表为全体小写字母的Trie
struct Trie {
  int head[maxnode]; // head[i]为第i个结点的左儿子编号
  int next[maxnode]; // next[i]为第i个结点的右兄弟编号
  char ch[maxnode];  // ch[i]为第i个结点上的字符
  int tot[maxnode];  // tot[i]为第i个结点为根的子树包含的叶结点总数
  int sz; // 结点总数
  long long ans; // 答案
  void clear() { sz = 1; tot[0] = head[0] = next[0] = 0; } // 初始时只有一个根结点

  // 插入字符串s（包括最后的'\0'），沿途更新tot
  void insert(const char *s) {
    int u = 0, v, n = strlen(s);
    tot[0]++;
    for(int i = 0; i <= n; i++) {
      // 找字符a[i]
      bool found = false;
      for(v = head[u]; v != 0; v = next[v])
        if(ch[v] == s[i]) { // 找到了
          found = true;
          break;
        }
      if(!found) {
        v = sz++; // 新建结点
        tot[v] = 0;
        ch[v] = s[i];
        next[v] = head[u];
        head[u] = v; // 插入到链表的首部
        head[v] = 0;
      }
      u = v;
      tot[u]++;
    }
  }

  // 统计LCP=u的所有单词两两的比较次数之和
  void dfs(int depth, int u) {
    if(head[u] == 0) // 叶结点
      ans += tot[u] * (tot[u] - 1) * depth;
    else {
      int sum = 0;
      for(int v = head[u]; v != 0; v = next[v])
        sum += tot[v] * (tot[u] - tot[v]); // 子树v中选一个串，其他子树中再选一个
      ans += sum / 2 * (2 * depth + 1); // 除以2是每种选法统计了两次
      for(int v = head[u]; v != 0; v = next[v])
        dfs(depth+1, v);
    }
  }

  // 统计
  long long count() {
    ans = 0;
    dfs(0, 0);
    return ans;
  }
};

#include<cstdio>
const int maxl = 1000 + 10;   // 每个单词最大长度

int n;
char word[maxl];
Trie trie;

int main() {
  int kase = 1;
  while(scanf("%d", &n) == 1 && n) {
    trie.clear();
    for(int i = 0; i < n; i++) {
      scanf("%s", word);
      trie.insert(word);
    }
    printf("Case %d: %lld\n", kase++, trie.count());
  }
  return 0;
}
