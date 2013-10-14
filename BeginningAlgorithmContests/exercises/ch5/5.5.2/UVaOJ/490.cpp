#include<iostream>
#include<cstdio>
#include<cstdlib> 
#include<cstring>
using namespace std;
int max(int x,int y) {return x<y?y:x;}
char a[150][150];
int len[150];
int main() {   
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
     cout << '\n' ;   //越len界的都是\0不输出 
    }    
    getchar();
    return 0;
}    
/*
Rene Decartes once said,
"I think, therefore I am."
*/
