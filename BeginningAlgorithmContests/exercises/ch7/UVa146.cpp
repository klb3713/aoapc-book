// UVa146 ID Codes
// Rujia Liu
// 题意：输入一个小写字符串，求字典序比它大的最小排列
// 算法：直接用next_permutation
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int main() {
  char s[100];
  while(scanf("%s", s) == 1 && s[0] != '#') {
    if(!next_permutation(s, s+strlen(s))) printf("No Successor\n");
    else printf("%s\n", s);
  }
  return 0;
}
