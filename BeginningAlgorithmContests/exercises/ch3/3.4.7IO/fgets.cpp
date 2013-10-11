//缺点：由于参数2000的存在，fgets每次只能读2000个字符，如果在程序中加入行数的计数（根据读的次数），计数就会出错，因此只能通过判断'\n'来进行计数。
#include<cstdio>
#include<ctime>
char s[2000];
int main()
{
 int n=0;
 FILE *fin,*fout,*buf;
 buf=fopen("buf.out","w");
 fin=fopen("string.in","r");
 fout=fopen("time","a");

 while(fgets(s,2000,fin)!=NULL) fputs(s,buf);
 fprintf(fout,"fgets:%.3lfs\n\n\n",(double)clock()/CLOCKS_PER_SEC);
 fclose(fin);
 return 0;
}
