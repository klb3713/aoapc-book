#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
 int r;
 while(cin >> r)
 {
  if(r==-1) break;
  cout <<"Round "<<r<<endl;
  char t[1024];
  int s1[26],s2[26],s=0,s_=0,l;
  memset(s1,0,sizeof(s1));
  memset(s2,0,sizeof(s2));
  scanf("%s\n",t); l=strlen(t);
  for(int i=0;i<l;i++) s1[t[i]-'a']=1;
  scanf("%s\n",t); l=strlen(t);
  int flag=1;
  for(int i=0;i<l;i++)
  {
   s2[t[i]-'a']=1;
   if(s1[t[i]-'a']==1) {s1[t[i]-'a']=s2[t[i]-'a']=0;}
   s=s_=0;
   for(int i=0;i<26;i++) {
    if(s1[i]) s++;
    if(s2[i]) s_++;
   }
   if(s==0&&flag) {cout <<"You win." << endl; flag=0;}
   else if(flag&&s_>=7) {cout << "You lose." << endl; flag=0;}
  }
  if(flag) cout << "You chickened out." << endl;
 }
 return 0;
}
/*
1
cheese
chese
2
cheese
abcdefg
3
cheese
abcdefgij
-1
*/
