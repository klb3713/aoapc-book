#include<stdio.h>

void print_subset(int n, int* B, int cur) {
  if(cur == n) {
    for(int i = 0; i < cur; i++)
      if(B[i]) printf("%d ", i); // 打印当前集合
    printf("\n");
    return;
  }
  B[cur] = 1; // 选第cur个元素
  print_subset(n, B, cur+1);
  B[cur] = 0; // 不选第cur个元素
  print_subset(n, B, cur+1);
}

int B[10];
int main() {
  print_subset(5, B, 0);
  return 0;
}
