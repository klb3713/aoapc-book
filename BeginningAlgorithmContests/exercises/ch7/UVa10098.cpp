// UVa10098 Generating Fast, Sorted Permutation
// Rujia Liu
// 题意：输入一个字符串，按字典序输出所有排列
// 算法：直接用next_permutation
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int main() {
  int T;
  char s[100];
  scanf("%d", &T);
  while(T--) {
    scanf("%s", s);
    int n = strlen(s);
    sort(s, s+n);
    do { printf("%s\n", s); } while(next_permutation(s, s+n));
    printf("\n");
  }
  return 0;
}
