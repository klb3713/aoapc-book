#include<cstdio>
#include<cstdlib>
#include<time.h>
int main()
{
 char c;
 int n=0;
 freopen("string.in","r",stdin);
 freopen("buf.out","w",stdout);
 while((c=getchar())!=EOF) putchar(c);
 FILE *fout;
 fout=fopen("time","a");
 fprintf(fout,"getchar:%.3lfs\n",(double)clock()/CLOCKS_PER_SEC);
 return 0;
}
