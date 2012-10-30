// LA4043 Ants
// Rujia Liu
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxn = 100 + 10;

const double INF = 1e30;

int n;
double W[maxn][maxn];
double Lx[maxn], Ly[maxn];   // 顶标
int left[maxn];          // left[i]为右边第i个点的匹配点编号
bool S[maxn], T[maxn];   // S[i]和T[i]为左/右第i个点是否已标记

bool eq(double a, double b) {
  return fabs(a-b) < 1e-9;
}

bool match(int i){
  S[i] = true;
  for(int j = 1; j <= n; j++) if (eq(Lx[i]+Ly[j], W[i][j]) && !T[j]){
    T[j] = true;
    if (!left[j] || match(left[j])){
      left[j] = i;
      return true;
    }
  }
  return false;
}

void update(){
  double a = INF;
  for(int i = 1; i <= n; i++) if(S[i])
    for(int j = 1; j <= n; j++) if(!T[j])
      a = min(a, Lx[i]+Ly[j] - W[i][j]);
  for(int i = 1; i <= n; i++) {
    if(S[i]) Lx[i] -= a;
    if(T[i]) Ly[i] += a;
  }
}

void KM() {
  for(int i = 1; i <= n; i++) {
    left[i] = Lx[i] = Ly[i] = 0;
    for(int j = 1; j <= n; j++)
      Lx[i] = max(Lx[i], W[i][j]);
  }
  for(int i = 1; i <= n; i++) {
    for(;;) {
      for(int j = 1; j <= n; j++) S[j] = T[j] = 0;
      if(match(i)) break; else update();
    }
  }
}

int main(){
  int kase = 0;
  while(scanf("%d", &n) == 1) {
    if(++kase > 1) printf("\n");

    int x1[maxn], y1[maxn], x2[maxn], y2[maxn];
    for(int i = 1; i <= n; i++) scanf("%d%d", &x1[i], &y1[i]);
    for(int i = 1; i <= n; i++) scanf("%d%d", &x2[i], &y2[i]);
    for(int i = 1; i <= n; i++) // ant colony
      for(int j = 1; j <= n; j++) // apple tree
        W[j][i] = -sqrt((double)(x1[i]-x2[j])*(x1[i]-x2[j]) + (double)(y1[i]-y2[j])*(y1[i]-y2[j]));
    KM(); // 最大权匹配
    for(int i = 1; i <= n; i++) printf("%d\n", left[i]);
  }
  return 0;
}
