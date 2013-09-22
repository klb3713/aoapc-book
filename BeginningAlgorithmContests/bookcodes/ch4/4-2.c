#include<stdio.h>
/* do NOT use this if x is very large or small */
int is_prime(int x){
  int i;
  for(i = 2; i*i <= x; i++)
    if(x % i == 0) return 0;
  return 1;
}

int main(){
  int i, m;
  scanf("%d", &m);
  for(i = m-2; i >= 3; i--)
    if(is_prime(i) && is_prime(i+2)) {
      printf("%d %d\n", i, i+2);
      break;
    }
  return 0;
}
