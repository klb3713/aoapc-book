// UVa375 Inscribed Circles and Isosceles Triangles
// Rujia Liu
// 题意：输入一个等腰三角形的底和高，从下往上连续画内切圆，直到半径小于给定值，求所有内切圆的周长和
// 算法：每画一个圆，在上方做一条切线，则问题转化为了一个较小的等腰三角形
#include<cstdio>
#include<cmath>
const double PI = acos(-1.0);

double solve(double B, double H) {
  double ang = atan(H/(B/2)), R = tan(ang/2) * B/2; // ang为腰和底的夹角
  if(R < 1e-6) return 0;
  return 2*PI*R + solve(B*(H-2*R)/H, H-2*R); // 根据相似三角形的比例计算新等腰三角形的底和高
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    double B, H;
    scanf("%lf%lf", &B, &H);
    printf("%13.6lf\n", solve(B, H));
    if(T) printf("\n");
  }
  return 0;
}
