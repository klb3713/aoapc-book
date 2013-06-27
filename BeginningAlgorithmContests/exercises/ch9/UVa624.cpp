// UVa624 CD
// Rujia Liu
// 题意：输入N, k和k首歌，选一些歌使得长度之和不超过但尽量接近N。要求输出方案
// 算法：价值和重量相同的0-1背包
#include<cstdio>
#include<cstring>
const int maxk = 20 + 5;
const int maxn = 20000 + 5;
int N, k, a[maxk], d[maxk][maxn];

void print(int i, int j) {
  if(i == 0) return;
  if(d[i-1][j]) print(i-1, j);
  else { print(i-1, j-a[i]); printf("%d ", a[i]); }
}

int main() {
  while(scanf("%d", &N) == 1) {
    scanf("%d", &k);
    for(int i = 1; i <= k; i++) scanf("%d", &a[i]);
    memset(d, 0, sizeof(d));
    d[0][0] = 1;
    for(int i = 1; i <= k; i++)
      for(int j = 0; j <= N; j++)
        if(d[i-1][j] || (j >= a[i] && d[i-1][j-a[i]])) d[i][j] = 1;
    int ans = N;
    while(!d[k][ans]) ans--;
    print(k, ans);
    printf("sum:%d\n", ans);
  }
  return 0;
}
