#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

bool is_alpha(char x){if(x>='A'&&x<='Z'||x>='a'&&x<='z') return true; return false;}

int main(){
    char s[5000];
    while(fgets(s,5000,stdin))
    {
        int len=strlen(s),count=0;
        bool flag=false;
        for(int i=0;i<len;i++) {
            if(!flag&&is_alpha(s[i])) flag=true;
            if(flag&&!is_alpha(s[i])) {flag=false; count++;}
            //for all else continue
        }
        if(flag) count++;
        printf("%d\n",count);
    }
    return 0;
}
