#include<stdio.h>
void inverse_pair(int* A, int x, int y, int* cnt, int* T) {
  if(y-x > 1){
    int m = x + (y-x)/2;
    int p = x, q = m, i = x;
    inverse_pair(A, x, m, cnt, T);
    inverse_pair(A, m, y, cnt, T);
    while(p < m || q < y) {
      if(q >= y || (p < m && A[p] <= A[q]))
        T[i++] = A[p++];
      else {
        T[i++] = A[q++];
        *cnt += m-p;
      }
    }
    for(i = x; i < y; i++) A[i] = T[i];
  }
}

int A[] = {1,1,1,1,1,1,1,1,1};
int T[] = {0,0,0,0,0,0,0,0,0};
int main(){
  int i, cnt = 0;;
  inverse_pair(A, 0, 9, &cnt, T);
  printf("%d\n", cnt);
  return 0;
}
