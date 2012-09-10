#include<stdio.h>
int A[100];

// 输出1~n的全排列
void print_permutation(int n, int* A, int cur) {
  int i, j;
  if(cur == n) { // 递归边界
    for(i = 0; i < n; i++) printf("%d ", A[i]);
    printf("\n");
  } else for(i = 1; i <= n; i++) { // 尝试在A[cur]中填各种整数i
    int ok = 1;
    for(j = 0; j < cur; j++)
      if(A[j] == i) ok = 0; // 如果i已经在A[0]~A[cur-1]出现过，则不能再选
    if(ok) {
      A[cur] = i;
      print_permutation(n, A, cur+1); // 递归调用
    }
  }
}

int main() {
  print_permutation(4, A, 0); 
  return 0;
}
