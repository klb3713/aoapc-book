// UVa10820 Send a Table
// Rujia Liu
// 题意：一道比赛题目输入两个整数x, y（1<=x,y<=n），输出某个函数f(x,y)。某人想交表，但是表太大，需要精简
// 已知很容易根据f(x,y)算出f(x*k, y*k)，因此后者就不需要打表了。输入n，输出表的大小。
// 问题抽象：输入n，输出有多少对(x,y)满足1<=x,y<=n, gcd(x,y)=1
// 算法：如果满足x<y的个数有f(n)个，那么答案就是2f(n)+1。不难发现f(n)=phi(2)+phi(3)+...+phi(n)
#include<cstdio>
#include<cmath>
const int maxn = 50000;
int phi[maxn+1], phi_psum[maxn+1];

void phi_table(int n) {
  phi[1] = 0;
  for(int i = 2; i <= n; i++) if(phi[i] == 0)
  for(int j = i; j <= n; j += i) {
    if(phi[j] == 0) phi[j] = j;
    phi[j] = phi[j] / i * (i-1);
  }
}

int main(){
  int n;
  phi_table(maxn);
  phi_psum[0] = 0;
  for(int i = 1; i <= maxn; i++)
    phi_psum[i] = phi_psum[i-1] + phi[i];
  while(scanf("%d", &n) == 1 && n)
    printf("%d\n",2*phi_psum[n] + 1);
  return 0;
}
