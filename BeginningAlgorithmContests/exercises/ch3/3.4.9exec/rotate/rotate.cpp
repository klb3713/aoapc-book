#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

#define MAXN 200
char s[MAXN][MAXN];

int main()
{
    /*Input n version
    int n;
    cin >> n;
    getchar(); //eat '\n'
    */
    
    freopen("rotate.in","r",stdin);
    freopen("rotate.out","w",stdout);
    fgets(s[0],MAXN,stdin);
    int n=strlen(s[0])-1;
    //printf("n=%d\n",n);
    for(int i=1;i<n;i++)    fgets(s[i],MAXN,stdin);
    for(int i=0;i<n;i++)
    {
        for(int j=n-1;j>=0;j--)
            putchar(s[j][i]);
        putchar('\n');
    }
    putchar('\n');
    
    return 0;
}
