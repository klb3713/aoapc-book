#include<stdio.h>
int main() {
  int n;
  while(scanf("%d", &n) == 1) {
    int k = 1, s = 0;
    for(;;) {
      s += k;
      if(s >= n) {
        if(k % 2 == 1)
          printf("TERM %d IS %d/%d\n", n, s-n+1, k-s+n);
        else
          printf("TERM %d IS %d/%d\n", n, k-s+n, s-n+1);
        break;
      }
      k++;
    }
  }
  return 0;
}
