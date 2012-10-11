// 注意：这个程序读写了非法内存（解释见书）
#include<stdio.h>
const int MAXN = 50;
int queue[MAXN];
int main() {
  int n, front, rear;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) queue[i] = i+1;
  front = 0;
  rear = n;
  while(front < rear) {
    printf("%d ", queue[front++]);
    queue[rear++] = queue[front++];
  }
  return 0;
}
