#include<iostream>
#include<cstdio>
using namespace std;
int main()
{
 int a,b;
 char c;
 freopen("calculator.in","r",stdin);
 freopen("calculator.out","w",stdout);
 scanf("%d",&a);
 c=getchar();
 while(c!='+'&&c!='-'&&c!='*') c=getchar();
 scanf("%d",&b);
 int ans;
 if(c=='+') ans=a+b;
 else if(c=='-') ans=a-b;
 else if(c=='*') ans=a*b;
 else ans=0;
 printf("%d %c %d = %d",a,c,b,ans);
 return 0;
}
