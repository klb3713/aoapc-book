// Uva10496	Collecting Beepers
// ³Â·æ
#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

struct Beeper
{
 int x;
 int y;
 bool collected;
};

int BeepersCnt, shortest, startX, startY;
Beeper beepers[16];

int fabs(int x)
{
 return x >= 0 ? x : -x;
}

void dfs(int x, int y, int col_cnt, int steps)
{
 if(steps >= shortest) return;
 if(col_cnt == BeepersCnt)
 {
  steps += fabs(startX - x) + fabs(startY - y);
  if(steps >= shortest) return;
  shortest = steps;
 }
 else
 {
  for(int i = 0; i < BeepersCnt; i++)
  {
   Beeper& b = beepers[i];
   if(b.collected) continue;

   b.collected = true;
   dfs(b.x, b.y, col_cnt + 1, steps + fabs(b.x - x) + fabs(b.y - y));
   b.collected = false;
  }
 }
}

int main()
{
 int T;
 scanf("%d", &T);
 
 while(T--)
 {
  int MaxX, MaxY;
  scanf("%d%d%d%d%d", &MaxX, &MaxY, &startX, &startY, &BeepersCnt);
  Beeper *pBeeper = beepers;
  for(int i = 0; i < BeepersCnt; i++)
  {
   int x, y;
   scanf("%d%d", &x, &y);
   if(x == startX && y == startY) continue;
   
   pBeeper->collected = false;
   pBeeper->x = x;
   pBeeper->y = y;
   pBeeper++;
  }  
  BeepersCnt = pBeeper - beepers;
  
  dfs(startX, startY, 0, 0);
  printf("The shortest path has length %d\n", shortest);
 }
 return 0;
}
