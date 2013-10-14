#include<iostream>
using namespace std;
int main()
{
 long long a,l,cs=0;
 for(;;)
 {
  cin >> a >> l;
  if(a<0&&l<0) break;
  cs++;
  cout << "Case " << cs <<": A = " << a<<", limit = "<<l<<", number of terms = " ;
  int t=1;
  do
  {
   if(a%2) {a=3*a+1;if(a>l) break;}
   else a/=2;
   t++;
  }while(a!=1);
  //我的理解：要求的是在超限（等于不算超）或停止之时已经出现的数字个数，出现1就停止，但不算超限，也要计进去。
  cout << t << endl;
 }
}
/*
 Sample Input

 3 100
 34 100
 75 250
 27 2147483647
 101 304
 101 303
 -1 -1
//e.g. 3->10->5->16->8->4->2->1 已经出现8个数字。
//e.g. 75->226->113 已经出现3个数字，再算就超限了，340不能出现。
Sample Output

 Case 1: A = 3, limit = 100, number of terms = 8
 Case 2: A = 34, limit = 100, number of terms = 14
 Case 3: A = 75, limit = 250, number of terms = 3
 Case 4: A = 27, limit = 2147483647, number of terms = 112
 Case 5: A = 101, limit = 304, number of terms = 26
 Case 6: A = 101, limit = 303, number of terms = 1

 */
