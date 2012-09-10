#include<stdio.h>
#include<assert.h>

int A[] = {1,2,3,4,5,6,7,8,9,10,11};

int bsearch(int* A, int x, int y, int v) {
  int m = x + (y-x)/2;
  if(y <= x) return -1;
  if(A[m] == v) return m;
  else return A[m]>v ? bsearch(A,x,m,v) : bsearch(A,m+1,y,v);
}

int main() {
  int i;
  for(i = 1; i <= 11; i++)
    assert(bsearch(A, 0, 11, i) == i-1);
  printf("Ok!\n");
  return 0;
}
