#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

char a[150][150];
int len[150];

int main()
{
    int n=0,maxl=-1;
    while((gets(a[n]))!=NULL) {
        len[n]=strlen(a[n]);
        if(len[n]>maxl) maxl=len[n];
        n++;
    }
    for(int i=0;i<maxl;i++){
     for(int j=n-1;j>=0;j--) {
      if(i<len[j]) cout << a[j][i];
      else cout << " " ;
     }
     cout << '\n' ;
    }
    getchar();
    return 0;
}
