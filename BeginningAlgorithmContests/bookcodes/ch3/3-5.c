#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAXN 5000 + 10
char buf[MAXN], s[MAXN];
int main(){
  int n, m = 0, max = 0;
  int i, j, k;
  fgets(buf, sizeof(s), stdin);
  n = strlen(buf);
  for(i = 0; i < n; i++)
    if(isalpha(buf[i])) s[m++] = toupper(buf[i]);
  for(i = 0; i < m; i++)
    for(j = i; j < m; j++) {
      int ok = 1;
      for(k = i; k <= j; k++)
        if(s[k] != s[i+j-k]) ok = 0;
      if(ok && j-i+1 > max) max = j-i+1;
    }
  printf("max = %d\n", max);
  return 0;
}
