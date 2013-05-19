/*
  习题2-5. 统计（stat）
  刘汝佳
*/

#include<stdio.h>
int main() {
  int i, n, a, m, count;
  FILE *fp;

  /* 第一次打开文件只是为了读取m */
  fp = fopen("stat.in", "r");
  fscanf(fp, "%d", &n);
  for(i = 0; i < n; i++)
    fscanf(fp, "%d", &a);
  fscanf(fp, "%d", &m);
  fclose(fp);

  /* 第二次打开文件完成统计 */
  count = 0;
  fp = fopen("stat.in", "r");
  fscanf(fp, "%d", &n);
  for(i = 0; i < n; i++) {
    fscanf(fp, "%d", &a);
    if(a < m) count++;
  }
  fclose(fp);

  fp = fopen("stat.out", "w");
  fprintf(fp, "%d\n", count);
  fclose(fp);

  return 0;
}
