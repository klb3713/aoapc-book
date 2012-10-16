// LA3485 Bridge: 自适应辛普森版
// Rujia Liu
#include<cstdio>
#include<cmath>

// 这里为了方便，把a声明成全局的。
// 这不是一个好的编程习惯，但在本题中却可以提高代码的可读性
double a; 

// simpson公式用到的函数
double F(double x) {
  return sqrt(1 + 4*a*a*x*x);
}

// 三点simpson法。这里要求F是一个全局函数
double simpson(double a, double b) {
  double c = a + (b-a)/2;
  return (F(a)+4*F(c)+F(b))*(b-a)/6;
}

// 自适应Simpson公式（递归过程）。已知整个区间[a,b]上的三点simpson值A
double asr(double a, double b, double eps, double A) {
  double c = a + (b-a)/2;
  double L = simpson(a, c), R = simpson(c, b);
  if(fabs(L+R-A) <= 15*eps) return L+R+(L+R-A)/15.0;
  return asr(a, c, eps/2, L) + asr(c, b, eps/2, R);
}

// 自适应Simpson公式（主过程）
double asr(double a, double b, double eps) {
  return asr(a, b, eps, simpson(a, b));
}

// 用自适应Simpson公式计算宽度为w，高度为h的抛物线长
double parabola_arc_length(double w, double h) {
  a = 4.0*h/(w*w); // 修改全局变量a，从而改变全局函数F的行为
  return asr(0, w/2, 1e-5)*2;
}

int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    int D, H, B, L;
    scanf("%d%d%d%d", &D, &H, &B, &L);
    int n = (B+D-1)/D; // 间隔数
    double D1 = (double)B / n;
    double L1 = (double)L / n;
    double x = 0, y = H;
    while(y-x > 1e-5) { // 二分法求解高度
      double m = x + (y-x)/2;
      if(parabola_arc_length(D1, m) < L1) x = m; else y = m;
    }
    if(kase > 1) printf("\n");
    printf("Case %d:\n%.2lf\n", kase, H-x);
  }
  return 0;
}