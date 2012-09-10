#include<stdio.h>
int f(int n){
  return n == 0 ? 1 : f(n-1)*n;
}
int main(){
  printf("%d\n", f(3));
  return 0;
}
