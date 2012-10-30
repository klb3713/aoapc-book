// UVa11383 Golden Tiger Claw
// Rujia Liu
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 500 + 10;
const int INF = 1000000000;

int W[maxn][maxn], n;
int Lx[maxn], Ly[maxn]; // 顶标
int left[maxn];         // left[i]为右边第i个点的匹配点编号
bool S[maxn], T[maxn];   // S[i]和T[i]为左/右第i个点是否已标记

bool match(int i){
  S[i] = true;
  for(int j = 1; j <= n; j++) if (Lx[i]+Ly[j] == W[i][j] && !T[j]){
    T[j] = true;
    if (!left[j] || match(left[j])){
      left[j] = i;
      return true;
    }
  }
  return false;
}

void update(){
  int a = INF;
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
      for(int j = 1; j <= n; j++) S[j] = T[j] = false;
      if(match(i)) break; else update();
    }
  }
}

int main(){
  while(scanf("%d", &n) == 1) {
    for(int i = 1; i <= n; i++)
      for(int j = 1; j <= n; j++)
        scanf("%d", &W[i][j]);
    KM();
    int sum = 0;
    for(int i = 1; i < n; i++) { printf("%d ", Lx[i]); sum += Lx[i]; } printf("%d\n", Lx[n]);
    for(int i = 1; i < n; i++) { printf("%d ", Ly[i]); sum += Ly[i]; } printf("%d\n", Ly[n]);
    printf("%d\n", sum + Lx[n] + Ly[n]);
  }
  return 0;
}
