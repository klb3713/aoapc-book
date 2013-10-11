//Conclusion: strlen() is an O(n) function;
//get1() is also an O(n) function;
//While using both,it's O(n^2).
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cstring>
#define MAXN 100000000
char s[MAXN];
FILE *fout;
int getn()
{
    srand(time(NULL));
    int n;
    n=(rand()%int(1e3))*(rand()%int(1e3)); //if using directly "int n=rand...",the program may sleep
    //printf("n1=%d\n",n);
    while(n<int(1e5)) n=rand()%int(1e3)*rand()%int(1e3);
    //printf("n2=%d\n",n);
}
void makedata()
{
    int n;
    n=getn();

    for(int i=0;i<n;++i) s[i]=rand()%80+29;
}
void get1()
{
 int tot=0,i,len;
 len=strlen(s);
 for(i=0;i<len;i++)
  if(s[i]=='1') tot++;
  fprintf(stdout,"There are %d character(s) '1' in the string.\n",tot);
  fprintf(stdout,"len=%d,'time=%.5lfs\n",len,(double)clock()/CLOCKS_PER_SEC);
 fprintf(fout,"len=%d,'time=%.5lfs\n",len,(double)clock()/CLOCKS_PER_SEC);
}
int main()
{
 //char x[8379873]; less or overmemory in linux
 //char x[2082000]; in windows
 //fgets(s,sizeof(s),stdin);

 fout=fopen("time","a");
 makedata();
 int len=strlen(s);
 printf("len=%d\n",len);
 if(len>100000) printf(">10^5\n"); else printf("!>10^5\n");
 get1();
 return 0;
}
