// LA3353  Optimal Bus Route Design
// 陈锋
#include<cassert>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int MAXN = 99 + 10, LARGEINT = 1<<30;
int n, W[MAXN][MAXN], Lx[MAXN], Ly[MAXN], left[MAXN];
bool S[MAXN], T[MAXN];

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
  int a = LARGEINT; 
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

void runcase(int kase)
{
    // 初始化二分图
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            W[i][j] = -10000;
    
    for(int i = 1; i <= n; i++)
    {
        while(true)
        {
            int j, w;
            scanf("%d", &j);
            if(j == 0) break;
            scanf("%d", &w);
            W[i][j] = max(W[i][j], -w);
        }
    }
    
    // 求最大边权值匹配
    KM();
    
    bool match = true;
    int ans = 0;
    for(int j = 1; j <= n; j++)
    {
        int i = left[j];
        if(W[i][j] == -10000) // 被迫匹配的边，没找到匹配
        {
            match = false;
            break;
        }
        ans += -W[i][j];
    }
    if(match) printf("%d\n", ans);
    else puts("N");
}

int main() {
    int kase = 1;
    while(true)
    {
        scanf("%d", &n);
        if(n == 0) break;
        runcase(kase++);
    }
    return 0;
}