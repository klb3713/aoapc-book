#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
 freopen("base1.in","r",stdin);
 freopen("base1.out","w",stdout);
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
 while(top) cout << s[top--];
 return 0;
}
