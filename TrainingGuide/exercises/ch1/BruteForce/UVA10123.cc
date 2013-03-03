// Uva10123	No Tipping
// 陈锋
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int MAXPKG = 20, LeftSupport = -15, RrighSupport = 15;

struct Package
{
 int position;
 int weight;
 bool removed;
 int torqueToLeft;
 int torqueToRight;
 
 inline void readline()
 {
  scanf("%d%d", &position, &weight);
  removed = false;
  position *= 10;  
  // todo:
  torqueToLeft = (position - LeftSupport ) * weight;
  torqueToRight = (position - RrighSupport) * weight;
 }
 
 inline void output()
 {
  printf("%d %d\n", position / 10, weight);
  #ifdef DEBUG
  printf("torques: %d %d\n", torqueToLeft, torqueToRight);
  #endif
 }
};

inline int getid(Package* packages,  int n)
{
 int id = 0, mask = 1;
 for(int i = 0; i < n; i++) 
 {
  if(!packages[i].removed) id |= mask;
  mask <<= 1;
 }
 return id;
}

bool visited[1<<20]; // 2 ^ 20

bool dfs(Package *packages, int* remPkgs, int removedCnt, int n, int leftTorque, int rightTorque)
{
 if(leftTorque < 0 || rightTorque > 0) return false;
 
 if(removedCnt ==  n) return true;
 
 for(int i = 0; i < n; i++)
 {
  if(!packages[i].removed && leftTorque >= packages[i].torqueToLeft && rightTorque <= packages[i].torqueToRight)
  {
   packages[i].removed = true;
   int id = getid(packages, n);
   if(!visited[id])
   {
    visited[id] = true;
    remPkgs[removedCnt] = i;
    if(dfs(packages, remPkgs, removedCnt + 1, n, leftTorque - packages[i].torqueToLeft, rightTorque - packages[i].torqueToRight))
     return true;    
   }
   packages[i].removed = false;
  }
 }
 return false;
}

int main()
{
 int Case = 1;
 Package packages[MAXPKG];
 int removed[MAXPKG];
 
 while(true)
 {
  int BoardLen, BoardWeight, n;
  scanf("%d%d%d", &BoardLen, &BoardWeight, &n);
  if(BoardLen == 0 && BoardWeight == 0 && n == 0) break;
  
  printf("Case %d:\n", Case++);
  BoardLen *= 10;
  
  int leftTorque = 15 * BoardWeight, rightTorque = -15 * BoardWeight;
  for(int i = 0; i < n; i++)
  {
   packages[i].readline();
   leftTorque += packages[i].torqueToLeft;
   rightTorque += packages[i].torqueToRight;
  }
  fill_n(visited, (1 << n), false);
  
  // 加上平板本身的力矩
  
  if(dfs(packages, removed, 0, n, leftTorque, rightTorque))
   for(int i = 0; i < n; i++)
    packages[removed[i]].output();
  else
   puts("Impossible");
 }
 return 0;
}
