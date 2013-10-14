#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int main()
{
    int n;
    char s[100];
    scanf("%d\n",&n);
    for(int i=1;i<=n;i++){
        cin.getline(s,100,'\n');
        int len=strlen(s);
        for(int j=0;j<len/2;j++) {char c=s[j]; s[j]=s[len-j-1]; s[len-j-1]=c;}
        printf("%s\n",s);
    }
    return 0;
}        
