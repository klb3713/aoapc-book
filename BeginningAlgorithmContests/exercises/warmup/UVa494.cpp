// UVa494 Kindergarten Counting Game 
// Rujia Liu
// 题意：统计输入每行的单词个数。单词为连续的字母（大小写均可）
#include<cstdio>
#include<cstring>
#include<cctype>
const int maxn = 10000;
char line[maxn];

int main() {
  int ch, last = '\0', cnt = 0;
  while(fgets(line, maxn, stdin) != NULL) {
    int cnt = 0, len = strlen(line);
    for(int i = 0; i < len; i++) {
      if(isalpha(line[i]) && (i == 0 || !isalpha(line[i-1]))) cnt++;
    }
    printf("%d\n", cnt);    
  }
  return 0;
}
