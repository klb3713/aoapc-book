#include <cstdio>

bool isalpha(char x)
{
    if(x<='z'&&x>='a'||x<='Z'&&x>='A')
        return true;
    else
        return false;
}

int main()
{
    char c;
    c=getchar();
    if(isalpha(c))
        printf("is alpha");
    else
        printf("Not alpha");
    return 0;
}
