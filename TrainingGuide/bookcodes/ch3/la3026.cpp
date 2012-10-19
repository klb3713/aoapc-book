// LA3026 Period
// Rujia Liu
#include<cstdio>
const int maxn = 1000000 + 10;
char P[maxn];
int f[maxn];

int main() {
  int n, kase = 0;
  while(scanf("%d", &n) == 1 && n) {
    scanf("%s", P);
    f[0] = 0; f[1] = 0; // µ›Õ∆±ﬂΩÁ≥ı÷µ
    for(int i = 1; i < n; i++) {
      int j = f[i];
      while(j && P[i]!=P[j]) j = f[j];
      f[i+1] = (P[i] == P[j] ? j+1 : 0);
    }

    printf("Test case #%d\n", ++kase);
    for(int i = 2; i <= n; i++)
      if(f[i] > 0 && i % (i - f[i]) == 0) printf("%d %d\n", i, i / (i - f[i]));
    printf("\n");
  }
  return 0;
}
