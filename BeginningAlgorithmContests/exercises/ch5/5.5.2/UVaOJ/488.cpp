#include<iostream>
using namespace std;
int main()
{
 int n,a,f;
 cin >> n;
 for(int i=1;i<=n;i++)
 {
  cin >> a >> f;
  for(int j=1;j<=f;j++)
  {
   for(int x=1;x<=a;x++){
    for(int y=1;y<=x;y++) cout << x;
    cout << endl;
   }
   for(int x=a-1;x>0;x--){
    for(int y=1;y<=x;y++) cout << x;
    cout << endl;
   }
   if(j<f) cout << endl;
  }
  if(i<n) cout << endl;
 }
 return 0;
}
