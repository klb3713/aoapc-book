// UVa445 Marvelous Mazes
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<cctype>
const int maxn = 10000;
char line[maxn];
int cnt;

void print(int ch, int x) {
  while(x--) printf("%c", ch);
  cnt = 0;
}

int main() {
  while(fgets(line, maxn, stdin) != NULL) {
    int len = strlen(line);
    cnt = 0;
    for(int i = 0; i < len; i++)
      if(isdigit(line[i])) cnt += line[i] - '0';
      else if(line[i] == '!') print('\n', 1);
      else if(line[i] == 'b') print(' ', cnt);
      else print(line[i], cnt);
    printf("\n");
  }
  return 0;
}
