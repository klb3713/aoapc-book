// LA3276  The Great Wall Game
// 陈锋
#include<cassert>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

struct Point
{
    int row, col;
    
    void read()
    {        
        scanf("%d%d", &row, &col);
    }
    
    void set(int r, int c)
    {
        row = r;
        col = c;
    }
    
    int dist(const Point& rhs) const
    {
        return abs(row - rhs.row) + abs(col - rhs.col);
    }
};

const int MAXN = 15 + 10, LARGEINT = 1<<30;
Point stones[MAXN], targets[MAXN];
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

int calc()
{
    // 初始化二分图
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            W[i][j] = -stones[i].dist(targets[j]);
    
    // 求最大边权值匹配
    KM();
    
    int result = 0;
    for(int i = 1; i <= n; i++)
        result += targets[i].dist(stones[left[i]]);
    
    return result;
}

void runcase(int kase)
{    
    int ans = LARGEINT;

    for(int i = 1; i <= n; i++)
        stones[i].read();
     
    // 目标为一列
    for(int c = 1; c <= n; c++)
    {
        for(int r = 1; r <= n; r++)
            targets[r].set(r, c);
        ans = min(ans, calc());        
    }
    
    // 目标为一行
    for(int r = 1; r <= n; r++)
    {
        for(int c = 1; c <= n; c++)
            targets[c].set(r, c);
        ans = min(ans, calc());
    }

    
    // 目标为正对角线
    for(int i = 1; i <= n; i++)
        targets[i].set(i, i); 
    ans = min(ans, calc());
    
    // 反对角线
    for(int i = 1; i <= n; i++)
        targets[i].set(i, n - i + 1);  
    ans = min(ans, calc());
    
    printf("Board %d: %d moves required.\n\n", kase, ans);
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