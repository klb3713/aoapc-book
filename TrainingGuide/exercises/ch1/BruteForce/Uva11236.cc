// Uva11236	Grocery store
// 陈锋
#include <cstdio>
#include <algorithm>

using namespace std;

// 这里有了a,b,c之后就计算出d的值，并且把a, b, c, d都放大100倍来避免整数输出。
// 先用效率最低的方法算出a, b, c的范围，然后将其用于程序剪枝。

int main()
{
 int a, b, c, x, y, d;
 
 for(a = 8; a <= 125; a++)
 {
  for(b = max(a, 50); b <= 592 && (a + b) < 2000; b++)
  {
   for(c = max(b, 120); c <= 884 && (a + b + c) < 2000; c++)
   {
    y = (a * b * c - 1000000);
    if(y > 0)
    {
     x = 1000000 * (a + b + c);
     d = x / y;
     if(d * y == x && d >= c && (a + b + c + d <= 2000))
      printf("%d.d %d.d %d.d %d.d\n", 
       a / 100, a % 100, b / 100, b % 100, c / 100, c % 100, d / 100, d % 100);
    }
   }
  }
 }
 return 0;
}
