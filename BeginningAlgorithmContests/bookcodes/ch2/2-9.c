#include<stdio.h>
#define INF 1000000000
int main(){
  FILE *fin, *fout;
  fin = fopen("data.in", "rb");
  fout = fopen("data.out", "wb");
  int x, n = 0, min = INF, max = -INF, s = 0;
  while(fscanf(fin, "%d", &x) == 1) {
    s += x;
    if(x < min) min = x;
    if(x > max) max = x;
    n++;
  }
  fprintf(fout, "%d %d %.3lf\n", min, max, (double)s/n);
  fclose(fin);
  fclose(fout);
  return 0;
}
