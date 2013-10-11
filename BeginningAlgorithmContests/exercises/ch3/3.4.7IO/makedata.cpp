#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cstring>
#define MAXN 10000
char s[MAXN<<1];
FILE *fout;
int getn()
{
    srand(time(NULL));
    int n;
    n=rand()%MAXN;
    //printf("n1=%d\n",n);
    while(n<100) n=rand()%MAXN;
    //printf("n2=%d\n",n);
}
void makedata()
{
    int n;
    n=getn();
    srand(time(NULL));
    for(int i=0;i<n;++i) s[i]=rand()%30+'A';
}
int main()
{
 //char x[8379873]; less or overmemory in linux
 //char x[2082000]; in windows
 //fgets(s,sizeof(s),stdin);

 fout=fopen("string.in","w");
 int n;
 srand(time(NULL));
 n=rand()%1000;
 while(n--){
 makedata();
 fputs(s,fout);
 fprintf(fout,"\n");
 }
 fclose(fout);
 return 0;
}
