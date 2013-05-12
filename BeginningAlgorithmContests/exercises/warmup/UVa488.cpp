// UVa488 Triangle Wave
// Rujia Liu
#include<cstdio>

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    int a, f;
    scanf("%d%d", &a, &f);
    while(f--) {
      for(int i = 1; i <= a*2-1; i++) {
        int cnt = (i <= a ? i : a*2-i);
        for(int j = 0; j < cnt; j++) printf("%d", cnt);
        printf("\n");
      }
      if(f) printf("\n");
    }
    if(T) printf("\n");
  }
  return 0;
}
