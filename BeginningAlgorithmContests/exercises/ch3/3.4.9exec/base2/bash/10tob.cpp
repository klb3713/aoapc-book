#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
 freopen("10.in","r",stdin);
 freopen("bto10.in","w",stdout);
 int b,n,x;
 cin >> b >> n;
 //10进制转n进制
 x=n;
 int s[100]={0},top=0;
 while(x)
 {
  s[++top]=x%b;
  x/=b;
 }
 cout << b << " ";
 while(top) cout << s[top--];
 cout << endl;
 return 0;
}
