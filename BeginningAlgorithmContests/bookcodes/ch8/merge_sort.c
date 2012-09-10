void merge_sort(int* A, int x, int y, int* T) {
  if(y-x > 1){
    int m = x + (y-x)/2;
    int p = x, q = m, i = x;
    merge_sort(A, x, m, T);
    merge_sort(A, m, y, T);
    while(p < m || q < y) {
      if(q >= y || (p < m && A[p] <= A[q]))
        T[i++] = A[p++];
      else
        T[i++] = A[q++];
    }
    for(i = x; i < y; i++) A[i] = T[i];
  }
}

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define MAXN 1000000

int A[MAXN], T[MAXN];

void assert_sorted() {
  int i;
  for(i = 0; i < MAXN-1; i++)
    assert(A[i] <= A[i+1]);
}

void test_ascending() {
  int i;
  for(i = 0; i < MAXN; i++)
    A[i] = i;
  merge_sort(A, 0, MAXN, T);
  assert_sorted();
}

void test_descending() {
  int i;
  for(i = 0; i < MAXN; i++)
    A[i] = -i;
  merge_sort(A, 0, MAXN, T);
  assert_sorted();
}

void test_random() {
  int i;
  for(i = 0; i < MAXN; i++)
    A[i] = (double)rand() / RAND_MAX * 1000000000;
  merge_sort(A, 0, MAXN, T);
  assert_sorted();
}

int main(){
  srand(time(NULL));
  test_ascending();
  test_descending();
  test_random();
  printf("Ok!\n");
  return 0;
}
