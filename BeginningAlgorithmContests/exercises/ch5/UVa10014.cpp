// UVa10014 Simple calculations
// Rujia Liu
// 题意：已知a[i]=(a[i-1]+a[i+1])/2-c[i]。输入a[0], a[n+1]和c[1~n]，求a[1]
// 算法：n个未知数（a[1~n]）和n个方程，手工消元可以直接解出a[1]的表达式
// 具体消元方法很多人的blog都有写，请自行搜索之 :)
// 表达式：a[1] = (n*a[0]+a[n+1]-2*sum{(n+1-i)c[i]}) / (n+1)

#include<cstdio>
int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    int n;
    double a0, an1, c;
    scanf("%d%lf%lf", &n, &a0, &an1);
    double sum = n*a0 + an1;
    for(int i = 1; i <= n; i++) {
      scanf("%lf", &c);
      sum -= (n+1-i) * c * 2;
    }
    printf("%.2lf\n", sum / (n+1));
    if(T) printf("\n");
  }
  return 0;
}
