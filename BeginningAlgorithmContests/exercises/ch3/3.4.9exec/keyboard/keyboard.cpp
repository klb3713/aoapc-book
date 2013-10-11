#include<cstdio>
int main()
{
 //Pre-process
 //自以为题目样例有误：pig应为p1 g3 g1，因为i键的第一个字母是g。（从p1可以看出题目是想用首字母表示某键）
 freopen("keyboard.in","r",stdin);
 freopen("keyboard.out","w",stdout);
 int a[30],m=0;
 for(int i=1;i<=6;i++)
  for(int j=1;j<=3;++j)
   a[m++] = j;
 a[m++] = 4;
 for(int i=1;i<=2; i++ )
  for(int j=1 ; j<=3 ; j++)
   a[m++]=j;
 a[m]=4;
 //Process
 char c;
 while((c=getchar())!='\n') printf("%c%d",c-a[c-'a']+1,a[c-'a']);
 return 0;
}
