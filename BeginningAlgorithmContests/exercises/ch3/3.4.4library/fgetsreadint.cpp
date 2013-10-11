#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
    char s[100];
    int a=0;
    FILE *fin;
    fin=stdin;
    fgets(s,sizeof(s),fin);
    int l=strlen(s);
    for(int i=0;i<l;i++)
        if(s[i]<='9'&&s[i]>='0')
            a=a*10+s[i]-'0';
    printf("%d",a);
    return 0;
}
