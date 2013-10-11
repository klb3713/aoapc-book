#include <cstdio>
#include <cstdlib>

char* fgets(char *s, int len, FILE *fp)
{
    char c;
    int i=0;
    while((c=getchar())!='\n' && i<len-1)
        s[i++]=c;
    s[i]='\0';
}

int main()
{
    char s[100];
    fgets(s, sizeof(s), stdin);
    printf("%s",s);
    return 0;
}

