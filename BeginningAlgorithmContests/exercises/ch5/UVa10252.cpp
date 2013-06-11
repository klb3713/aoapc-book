// UVa10252 Common Permutation
// Rujia Liu
// 题意：
// 给两个小写字符串a, b，找一个最长的字符串x，使得x的某一个排列是a的子序列（不一定连续），且x的某一个排列是b的子序列（不一定连续）
// 算法：x中所有字符应该是按顺序排列，对于每一个字符ch，如果它在a中出现了c1次，在b中出现了c2次，那么在答案中应出现min(c1,c2)次
// 注意事项：输入可能有空行，应用fgets输入整行
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

// 字符串s中字符ch出现的次数
int count(const char* s, int ch) {
  int cnt = 0, n = strlen(s);
  for(int i = 0; i < n; i++)
    if(s[i] == ch) cnt++;
  return cnt;
}

const int maxn = 1000 + 10;
char a[maxn], b[maxn];

int main() {
  while(fgets(a, maxn, stdin) != NULL) {
    fgets(b, maxn, stdin);
    for(int ch = 'a'; ch <= 'z'; ch++) {
      int cnt = min(count(a, ch), count(b, ch));
      while(cnt--) printf("%c", ch);
    }
    printf("\n");
  }
  return 0;
}
