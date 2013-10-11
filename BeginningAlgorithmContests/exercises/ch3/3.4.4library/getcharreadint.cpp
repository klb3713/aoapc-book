#include <cstdio>

int main()
{
    int a=0;
    char c;
    while((c=getchar()) != '\n')
        if(c<='9' && c>='0')
            a = a*10 + c-'0';
    printf("%d",a);
    return 0;
}
