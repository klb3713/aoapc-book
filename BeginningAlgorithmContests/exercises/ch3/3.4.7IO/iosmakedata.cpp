#include<cstdio>
#include<cstdlib>
#include<ctime>
int main(){
  freopen("ios.in","w", stdout);
  int n = 1000000 * (double)rand() / RAND_MAX;
  printf("%d\n", n);
  for(int i=1; i<=n; i++)  printf("%d ", rand());
  return 0;
}
