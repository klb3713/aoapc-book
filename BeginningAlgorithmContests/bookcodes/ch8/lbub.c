#include<stdio.h>
#include<assert.h>

int A[] = {1,3,5,7,9,11,13,15,17,19,21};
int B[] = {1,1,1,3,3,3,5,5,5,7,7,7,9,9,9};

int lower_bound(int* A, int x, int y, int v) {
  int m;
  while(x < y) {
    m = x+(y-x)/2;
    if(A[m]>=v) y=m; else x=m+1;
  }
  return x;
}

int upper_bound(int* A, int x, int y, int v) {
  int m;
  while(x < y) {
    m = x+(y-x)/2;
    if(A[m]<=v) x=m+1; else y=m;
  }
  return x;
}

int main() {
  int i;
  for(i = 1; i <= 21; i++)
    printf("%d\n", upper_bound(A, 0, 11, i));
  for(i = 0; i <= 11; i++)
    printf("%d %d\n", i, upper_bound(B, 0, 15, i));
  printf("Ok!\n");
  return 0;
}
