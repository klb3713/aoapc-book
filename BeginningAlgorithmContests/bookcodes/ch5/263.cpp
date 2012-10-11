#include<stdio.h>
#include<string.h>

int get_next(int x) {
  int a, b, n;
  char s[10];
  sprintf(s, "%d", x);
  n = strlen(s);
  for(int i = 0; i < n; i++)
    for(int j = i+1; j < n; j++)
      if(s[i] > s[j]) {
        char t = s[i]; s[i] = s[j]; s[j] = t;
      }
  sscanf(s, "%d", &b);
  for(int i = 0; i < n/2; i++) {
    char t = s[i]; s[i] = s[n-1-i]; s[n-1-i] = t;
  }
  sscanf(s, "%d", &a);
  return a - b;
}

int num[2000], count;
int main() {
  scanf("%d", &num[0]);
  printf("%d", num[0]);
  count = 1;
  for(;;) {
    num[count] = get_next(num[count-1]);
    printf(" -> %d", num[count]);
    int found = 0;
    for(int i = 0; i < count; i++)
        if(num[i] == num[count]) { found = 1; break; }
    if(found) break;
    count++;
  }
  printf("\n");
  return 0;
}
