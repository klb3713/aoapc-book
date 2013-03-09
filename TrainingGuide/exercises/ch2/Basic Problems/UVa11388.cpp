// UVa11388 GCD LCM
// Rujia Liu
#include<cstdio>
int main() {
  int T, G, L;
  scanf("%d", &T);
  while(T--) {
    scanf("%d%d", &G, &L);
    if(L%G) printf("-1\n"); else printf("%d %d\n", G, L);
  }
  return 0;
}