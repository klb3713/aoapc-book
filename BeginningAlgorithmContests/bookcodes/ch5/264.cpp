#include<stdio.h>
int main() {
  int n;
  while(scanf("%d", &n) == 1) {
    int k = 1, s = 0;
    for(;;) {
      s += k;
      if(s >= n) {
        printf("%d/%d\n", s-n+1, k-s+n);
        break;
      }
      k++;
    }
  }
  return 0;
}
