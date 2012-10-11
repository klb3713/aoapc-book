#include<stdio.h>
#include<math.h>
int main() {
  int n;
  while(scanf("%d", &n) == 1) {
    int k = (int)floor((sqrt(8.0*n+1)-1)/2 - 1e-9)+1;
    int s = k*(k+1)/2;
    if(k % 2 == 1)
      printf("TERM %d IS %d/%d\n", n, s-n+1, k-s+n);
    else
      printf("TERM %d IS %d/%d\n", n, k-s+n, s-n+1);
  }
  return 0;
}
