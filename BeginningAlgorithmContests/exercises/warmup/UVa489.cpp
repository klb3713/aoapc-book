// UVa489 Hangman Judge
// Rujia Liu
#include<cstdio>
#include<cstring>
const int maxn = 100;
int round, left, chance;
char s[maxn], s2[maxn];
bool win, lose;

void guess(char ch) {
  bool bad = true;
  for(int i = 0; i < strlen(s); i++)
    if(s[i] == ch) { left--; s[i] = ' '; bad = false; }
  if(bad) --chance;
  if(!chance) lose = true;
  if(!left) win = true;
}

int main() {
  while(scanf("%d%s%s", &round, s, s2) == 3 && round != -1) {
    printf("Round %d\n", round);
    win = lose = false;
    left = strlen(s);
    chance = 7;
    for(int i = 0; i < strlen(s2); i++) {
      guess(s2[i]);
      if(win || lose) break;
    }
    if(win) printf("You win.\n");
    else if(lose) printf("You lose.\n");
    else printf("You chickened out.\n");
  }
  return 0;
}
