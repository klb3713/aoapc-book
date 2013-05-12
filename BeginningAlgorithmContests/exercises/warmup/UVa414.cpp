// UVa414 Machined Surfaces
// Rujia Liu
#include<cstdio>
#include<cstring>
const int maxn = 30;
char line[maxn];

int main() {
  int n;
  while(scanf("%d\n", &n) == 1 && n) {
    int tot = 0, mincnt = maxn;
    for(int i = 0; i < n; i++) {
      fgets(line, maxn, stdin);
      int cnt = 0;
      for(int j = 0; j < strlen(line); j++)
        if(line[j] == ' ') cnt++;
      tot += cnt;
      if(cnt < mincnt) mincnt = cnt;
    }
    printf("%d\n", tot - mincnt * n);
  }
  return 0;
}
