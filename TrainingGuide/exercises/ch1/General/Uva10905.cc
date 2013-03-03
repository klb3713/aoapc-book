// Uva10905	Children's Game
// ³Â·æ
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int MAXN = 64;
string numbers[MAXN];
int indice[MAXN];

inline bool cmp(int x, int y)
{
 string xy = numbers[x] + numbers[y];
 string yx = numbers[y] + numbers[x];
 return xy > yx;
}

int main()
{
 while(true)
 {
  int i, N;
  cin>>N;
  if(N == 0) break;
  
  for(i = 0; i < N; i++)
  {
   cin>>numbers[i];
   indice[i] = i;
  }
  
  sort(indice, indice + N, cmp);
  
  for(i = 0; i < N; i++) cout<<numbers[indice[i]];
  cout<<endl;
 }

 return 0;
}
