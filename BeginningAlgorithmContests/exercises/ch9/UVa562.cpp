// UVa562 Dividing coins
// Rujia Liu
// 题意：给m<=100个硬币，每个面值<=500，要求分成两组，面值之和尽量接近。输出面值之和的差
// 算法：背包问题。背包容量为floor(sum/2)，价值和重量相等。d[i][j]
#include<cstdio>
#include<cstring>
const int maxm = 100 + 5;
const int maxv = 500;
int m, a[maxm], d[maxm*maxv];

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &m);
    int sum = 0;
    for(int i = 0; i < m; i++) { scanf("%d", &a[i]); sum += a[i]; }
    int V = sum / 2;

    memset(d, 0, sizeof(d));
    d[0] = 1;
    for(int i = 0; i < m; i++)
      for(int j = V-1; j >= 0; j--)
        if(d[j] && j + a[i] <= V) d[j + a[i]] = 1;

    int ans = V;
    while(!d[ans]) ans--;
    printf("%d\n", sum-ans*2);
  }
  return 0;
}
