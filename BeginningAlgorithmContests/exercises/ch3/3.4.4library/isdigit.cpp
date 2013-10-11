#include <cstdio>

bool isdigit(const char s )
{
    if(s>='0'&&s<='9')
        return true;
    else
        return false;
}

int main()
{
    char x;
    x=getchar();
    if(isdigit(x))  printf("Yes");
    else    printf("NO");
    return 0;
}
