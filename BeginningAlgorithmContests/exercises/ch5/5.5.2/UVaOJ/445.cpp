#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

char a[150];

int main()
{
    int ch, sum = 0;
    while((ch = getchar()) != EOF)
    {
        if(ch =='b')    ch = ' ';
        if(ch>='0' && ch<='9'){
            sum += ch-'0';
        }
        else if(ch == '!' || ch == '\n'){
            printf("\n");
        }
        else{
            for(int i=0; i<sum; i++)    printf("%c", ch);
            sum = 0;
        }
    }
    
    return 0;
}
