#include<stdio.h>
#include<assert.h>

int A[] = {1,2,3,4,5,6,7,8,9,10,11};

int bsearch(int* A, int x, int y, int v) {
  int m;
  while(x < y) {
    m = x+(y-x)/2;
    if(A[m] == v) return m;
    else if(A[m] > v) y = m;
    else x = m+1;
  }
  return -1;
}

int main() {
  int i;
  for(i = 1; i <= 11; i++)
    assert(bsearch(A, 0, 11, i) == i-1);
  printf("Ok!\n");
  return 0;
}
