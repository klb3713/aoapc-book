#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
using namespace std;

int strchr(char c,const char s[])
{
    int l=strlen(s);
    for(int i=0;i<l;i++) if(s[i]==c) return i;
    return -1;
}

int main(){
    char a[100],b;
    scanf("%s",a);
    while(!isalpha(b)) scanf("%c",&b);
    if(strchr(b,a)>=0) printf("The first char %c is at position %d in %s.\n",b,strchr(b,a),a);
    else printf("Not found.\n");

    return 0;
}
