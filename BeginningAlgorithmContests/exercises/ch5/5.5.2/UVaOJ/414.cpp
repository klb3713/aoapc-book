#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib> 
using namespace std;
int main(){
    char s[15][30];
    int n;
    scanf("%d",&n);
    while(n>0){
         getchar(); //process the extra '\n' 
         int bs=0;
         int minb=30;
         for(int i=1;i<=n;i++){
              fgets(s[i],30,stdin);   
              int b=0;
              for(int j=0;j<25;j++){ 
               if(s[i][j]==' ') {b++; bs++;}
               }
              if(b<minb) minb=b;
         }    
         printf("%d\n",bs-minb*n);
         scanf("%d",&n);
    }       
    return 0;
}    
/*
4
XXXX                XXXXX
XXX               XXXXXXX
XXXXX                XXXX
XX                 XXXXXX
2
XXXXXXXXXXXXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXXXX
1
XXXXXXXXX              XX
0
*/
