// UVa457 Linear Cellular Automata
// Rujia Liu
// 题意：有一个数组A[1~40]，其中A[20]=1，其他为0。输入一个数组DNA[0~9]，按以下方法模拟50次：
// 同时把每个数A[i]替换为DNA[A[i-1]+A[i]+A[i+1]]，其中越界A[i]的按0算
#include<cstdio>
#include<cstring>
int A[50], oldA[50], DNA[10];
const char* s = " .xW";

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    for(int i = 0; i < 10; i++) scanf("%d", &DNA[i]);
    memset(A, 0, sizeof(A));
    memset(oldA, 0, sizeof(oldA));
    A[20] = 1;
    for(int day = 0; day < 50; day++) {
      for(int i = 1; i <= 40; i++) {
        oldA[i] = A[i];
        printf("%c", s[A[i]]);
      }
      printf("\n");
      for(int i = 1; i <= 40; i++)
        A[i] = DNA[oldA[i-1]+oldA[i]+oldA[i+1]];
    }
    if(T) printf("\n");
  }
  return 0;
}
